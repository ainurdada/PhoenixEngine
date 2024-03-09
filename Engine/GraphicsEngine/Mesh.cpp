#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex> verteces, const std::vector<int> indexes)
{
	for (const Vertex& v : verteces) {
		m_verteces.push_back(v);
	}
	for (int i : indexes)
	{
		this->indexes.push_back(i);
	}

	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(Vertex) * m_verteces.size();

	vertexData.pSysMem = m_verteces.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;


	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * indexes.size();

	indexData.pSysMem = this->indexes.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
}
