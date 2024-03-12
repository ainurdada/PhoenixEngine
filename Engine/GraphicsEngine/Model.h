#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <wrl.h>
#include <vector>

#include "Mesh.h"
#include "ConstantBuffer.h"

class Model
{
	friend class RenderComponent;

	struct ConstantData
	{
		SMath::Matrix WorldViewProjection;
	};
	static_assert((sizeof(ConstantData) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

public:
	bool Initialize(const LPCWSTR filePath);
	void Release();
private:
	void Draw(const SMath::Matrix& modelMatrix);
	void ProcessNode(aiNode* node, const aiScene* scene, const DirectX::XMMATRIX& parentTransformMatrix);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, DirectX::XMMATRIX& transformMatrix);
	TextureStorageType DetermineTextureStorageType(const aiScene* pScene, aiMaterial* pMat, unsigned int index, aiTextureType textureType);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* pMaterial, aiTextureType textureType, const aiScene* pScene);
	int GetTextureIndex(aiString* pStr);

	std::vector<Mesh> meshes;
	std::string directory = "";
	ConstantBuffer<ConstantData> constant_data;
	ID3D11Buffer* transform_buffer = nullptr;
};