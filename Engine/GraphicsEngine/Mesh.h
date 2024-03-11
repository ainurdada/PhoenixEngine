#pragma once
class Mesh;

#include <vector>

#include "Graphics.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


class Mesh
{
public:
	Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<Vertex>& verteces, std::vector<int>& indexes);
	Mesh(const Mesh& mesh);
	void Draw();
private:
	VertexBuffer<Vertex> vb; 
	IndexBuffer ib;
	ID3D11DeviceContext* deviceContext;
};

