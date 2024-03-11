#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <wrl.h>
#include <vector>

#include "Mesh.h"

class Model
{
public:
	bool Initialize(const LPCWSTR filePath);
	void Draw();

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Mesh> meshes;
};