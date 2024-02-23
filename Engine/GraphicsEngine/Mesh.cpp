#include "Mesh.h"

Mesh::Mesh(std::vector<Vec4> XMPoints, std::vector<int> indexes)
{
	for (Vec4 p : XMPoints) {
		DirectX::XMFLOAT4 XMp(p.x, p.y, p.z, p.w);
		this->XMPoints.push_back(XMp);
	}

	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * this->XMPoints.size();

	vertexData.pSysMem = &(this->XMPoints[0]);
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;


	this->indexes = indexes;
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * this->indexes.size();

	indexData.pSysMem = &(this->indexes[0]);
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
}
