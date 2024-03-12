#pragma once
class Mesh;

#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

class Mesh
{
	friend class Model;
public:
	Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<Vertex>& verteces, std::vector<int>& indexes, std::vector<Texture>& textures);
	Mesh(const Mesh& mesh);
private:
	void Draw();
	VertexBuffer<Vertex> vb; 
	IndexBuffer ib;
	ID3D11DeviceContext* deviceContext;
	std::vector<Texture> textures;
};

