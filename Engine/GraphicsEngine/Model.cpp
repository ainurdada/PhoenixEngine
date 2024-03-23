#include <codecvt>

#include "Model.h"
#include "../../App/Game.h"
#include "../../Basic/Constants/Colors.h"
#include "../../Lib/Tools/StringHelper.h"

using namespace DirectX;
bool Model::Initialize(const LPCWSTR filePath)
{
	// Create transform buffer
	D3D11_BUFFER_DESC transformBufDesc = {};
	transformBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	transformBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transformBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	transformBufDesc.MiscFlags = 0;
	transformBufDesc.StructureByteStride = 0;
	transformBufDesc.ByteWidth = sizeof(ConstantData);
	Game::instance->graphics.GetDevice()->CreateBuffer(&transformBufDesc, nullptr, &transform_buffer);

	constant_data.Initialize(Game::instance->graphics.GetDevice().Get(), Game::instance->graphics.GetContext());
	dir_light_data.Initialize(Game::instance->graphics.GetDevice().Get(), Game::instance->graphics.GetContext());
	point_light_data.Initialize(Game::instance->graphics.GetDevice().Get(), Game::instance->graphics.GetContext());

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	this->directory = StringHelper::GetDirectoryFromPath(converter.to_bytes(filePath));

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(converter.to_bytes(filePath),
											 aiProcess_Triangulate
											 | aiProcess_ConvertToLeftHanded
	);
	if (nullptr == scene)
	{
		return false;
	}

	ProcessNode(scene->mRootNode, scene, XMMatrixIdentity());
	return true;
}

void Model::Release()
{
	transform_buffer->Release();
}

void Model::Draw(const SMath::Matrix& modelMatrix)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		// constant buffer
		SMath::Matrix world = SMath::Matrix(meshes[i].GetTransformMatrix()) * modelMatrix;
		constant_data.data.WorldViewProjection = XMMatrixTranspose(
			world
			* Game::instance->mainCamera->ViewMatrix()
			* Game::instance->mainCamera->ProjectionMatrix()
		);
		constant_data.data.World = XMMatrixTranspose(world);
		constant_data.data.ViewerPos = {
			Game::instance->mainCamera->transform.position().x,
			Game::instance->mainCamera->transform.position().y,
			Game::instance->mainCamera->transform.position().z,
			1
		};
		constant_data.ApplyChanges();

		// direction light buffer
		dir_light_data.data.direction = Game::instance->graphics.light.dirLight.direction;
		dir_light_data.data.intensity = Game::instance->graphics.light.dirLight.intensity;
		dir_light_data.data.KaSpecPowKsX = Game::instance->graphics.light.dirLight.KaSpecPowKsX;
		dir_light_data.ApplyChanges();

		// point light buffer
		if (Game::instance->graphics.light.pointLights.size() != 0)
		{
			point_light_data.data.position = Game::instance->graphics.light.pointLights[0].position;
			point_light_data.data.intensity = Game::instance->graphics.light.pointLights[0].intensity;
			point_light_data.ApplyChanges();
		}

		Game::instance->graphics.GetContext()->VSSetConstantBuffers(0, 1, constant_data.GetAddressOf());
		Game::instance->graphics.GetContext()->PSSetConstantBuffers(0, 1, constant_data.GetAddressOf());
		Game::instance->graphics.GetContext()->PSSetConstantBuffers(1, 1, dir_light_data.GetAddressOf());
		Game::instance->graphics.GetContext()->PSSetConstantBuffers(2, 1, point_light_data.GetAddressOf());
		meshes[i].Draw();
	}
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, const DirectX::XMMATRIX& parentTransformMatrix)
{
	XMMATRIX nodeTransformMatrix = XMMatrixTranspose(XMMATRIX(&node->mTransformation.a1)) * parentTransformMatrix;

	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene, nodeTransformMatrix));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, nodeTransformMatrix);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, DirectX::XMMATRIX& transformMatrix)
{
	// Data to fill
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	// Get vertices
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.Pos.x = mesh->mVertices[i].x;
		vertex.Pos.y = mesh->mVertices[i].y;
		vertex.Pos.z = mesh->mVertices[i].z;
		vertex.Pos.w = 1;

		if (mesh->HasNormals())
		{
			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;
			vertex.Normal.w = 0;
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.Tex.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.Tex.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	// Get indices
	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	std::vector<Texture> textures;
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<Texture> diffuseTetures = LoadMaterialTextures(material, aiTextureType_DIFFUSE, scene);
	textures.insert(textures.end(), diffuseTetures.begin(), diffuseTetures.end());

	return Mesh(Game::instance->graphics.GetDevice().Get(), Game::instance->graphics.GetContext(), vertices, indices, textures, transformMatrix);
}

TextureStorageType Model::DetermineTextureStorageType(const aiScene* pScene, aiMaterial* pMat, unsigned int index, aiTextureType textureType)
{
	if (pMat->GetTextureCount(textureType) == 0)
		return TextureStorageType::None;

	aiString path;
	pMat->GetTexture(textureType, index, &path);
	std::string texturePath = path.C_Str();

	if (texturePath[0] == '*')
	{
		if (pScene->mTextures[0]->mHeight == 0)
		{
			return TextureStorageType::EmbeddedIndexCompressed;
		}
		else
		{
			assert("SUPPORT DOES NOT EXIST FOR INDEXED NON COMPRESSED TEXTURES!" && 0);
			return TextureStorageType::EmbeddedIndexNonCompressed;
		}
	}

	if (auto pTex = pScene->GetEmbeddedTexture(texturePath.c_str()))
	{
		if (pTex->mHeight == 0)
		{
			return TextureStorageType::EmbeddedCompressed;
		}
		else
		{
			assert("SUPPORT DOES NOT EXIST FOR EMBEDDED NON COMPRESSED TEXTURES!" && 0);
			return TextureStorageType::EmbeddedNonCompressed;
		}
	}

	if (texturePath.find('.') != std::string::npos)
	{
		return TextureStorageType::Disk;
	}

	return TextureStorageType::None;
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* pMaterial, aiTextureType textureType, const aiScene* pScene)
{
	std::vector<Texture> materialTextures;
	TextureStorageType storageType = TextureStorageType::Invalid;
	unsigned int textureCount = pMaterial->GetTextureCount(textureType);
	ID3D11Device* device = Game::instance->graphics.GetDevice().Get();

	if (textureCount == 0)
	{
		storageType = TextureStorageType::None;
		aiColor3D aiColor(0, 0, 0);
		switch (textureType)
		{
		case aiTextureType_DIFFUSE:
			pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
			if (aiColor.IsBlack())
			{
				materialTextures.push_back(Texture(device, Basic::UnloadedTextureColor, textureType));
				return materialTextures;
			}
			materialTextures.push_back(Texture(device, SMath::Color(aiColor.r, aiColor.g, aiColor.b), textureType));
			return materialTextures;
		}
	}
	else
	{
		for (UINT i = 0; i < textureCount; i++)
		{
			aiString path;
			pMaterial->GetTexture(textureType, i, &path);
			TextureStorageType storageType = DetermineTextureStorageType(pScene, pMaterial, i, textureType);
			switch (storageType)
			{
			case TextureStorageType::EmbeddedIndexCompressed:
			{
				int index = GetTextureIndex(&path);
				Texture embeddedIndexTexture(device,
											 reinterpret_cast<uint8_t*>(pScene->mTextures[index]->pcData),
											 pScene->mTextures[index]->mWidth,
											 textureType);
				materialTextures.push_back(embeddedIndexTexture);
				break;
			}
			case TextureStorageType::EmbeddedCompressed:
			{
				const aiTexture* pTexture = pScene->GetEmbeddedTexture(path.C_Str());
				Texture embeddedTexture(device,
										reinterpret_cast<uint8_t*>(pTexture->pcData),
										pTexture->mWidth,
										textureType);
				materialTextures.push_back(embeddedTexture);
				break;
			}
			case TextureStorageType::Disk:
			{
				std::string fileName = this->directory + '\\' + path.C_Str();
				Texture diskTexture(device, fileName, textureType);
				materialTextures.push_back(diskTexture);
				break;
			}
			}
		}
	}

	if (materialTextures.size() == 0)
	{
		materialTextures.push_back(Texture(device, Basic::UnhandledTextureColor, aiTextureType_DIFFUSE));
	}
	return materialTextures;
}

int Model::GetTextureIndex(aiString* pStr)
{
	assert(pStr->length >= 2);
	return atoi(&pStr->C_Str()[1]);
}
