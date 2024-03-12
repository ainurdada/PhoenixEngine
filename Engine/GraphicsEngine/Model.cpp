#include <codecvt>


#include "Model.h"
#include "../../App/Game.h"
#include "../../Basic/Constants/Colors.h"
#include "../../Lib/Tools/StringHelper.h"
bool Model::Initialize(const LPCWSTR filePath)
{
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

    ProcessNode(scene->mRootNode, scene);
    return true;
}

void Model::Draw()
{
    for (int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw();
    }
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (UINT i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (UINT i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
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

    return Mesh(Game::instance->graphics.GetDevice().Get(), Game::instance->graphics.GetContext(), vertices, indices, textures);
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
