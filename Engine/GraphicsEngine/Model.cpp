#include <codecvt>


#include "Model.h"
#include "../../App/Game.h"
bool Model::Initialize(const LPCWSTR filePath)
{
	//Create an instance of the Importer class
    Assimp::Importer importer;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(converter.to_bytes(filePath),
                                             aiProcess_Triangulate 
                                            | aiProcess_ConvertToLeftHanded
    );

    // If the import failed, report it
    if (nullptr == scene)
    {
        return false;
    }

    ProcessNode(scene->mRootNode, scene);
    // We're done. Everything will be cleaned up by the importer destructor
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

    return Mesh(Game::instance->graphics.GetDevice().Get(), Game::instance->graphics.GetContext(), vertices, indices);
}
