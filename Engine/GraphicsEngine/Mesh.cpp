#include "Mesh.h"

Mesh::Mesh(const std::vector<Vec4> points, const std::vector<int> indexes)
{
	this->indexes = indexes;

	for (Vec4 p : points) {
		DirectX::XMFLOAT4 XMp(p.x, p.y, p.z, p.w);
		XMPoints.push_back(XMp);
	}

	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * XMPoints.size();

	vertexData.pSysMem = XMPoints.data();
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
