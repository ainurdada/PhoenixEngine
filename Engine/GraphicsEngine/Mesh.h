#pragma once
class Mesh;

#include <vector>

#include "Graphics.h"
#include "Vertex.h"


class Mesh
{
public:
	Mesh() {};
	Mesh(const std::vector<Vertex> verteces, const std::vector<int> indexes);
public:
	D3D11_BUFFER_DESC vertexBufDesc = {};
	D3D11_BUFFER_DESC indexBufDesc = {};
	D3D11_SUBRESOURCE_DATA vertexData = {};
	D3D11_SUBRESOURCE_DATA indexData = {};
	ID3D11Buffer* vb; 
	ID3D11Buffer* ib;
	std::vector<Vertex> m_verteces;
	std::vector<int> indexes;
};

