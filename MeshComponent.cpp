#include "MeshComponent.h"

MeshComponent::MeshComponent(const Graphics& graphics, const std::vector<Vec4>& points, const std::vector<int>& indexes)
{
	for (Vec4 p : points) {
		DirectX::XMFLOAT4 XMp(p.x, p.y, p.z, p.a);
		this->points.push_back(XMp);
	}

	D3D11_BUFFER_DESC vertexBufDesc = {};
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * this->points.size();

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = &(this->points[0]);
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	graphics.GetDevice()->CreateBuffer(&vertexBufDesc, &vertexData, &vb);


	this->indexes = indexes;
	D3D11_BUFFER_DESC indexBufDesc = {};
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * this->indexes.size();

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = &(this->indexes[0]);
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	graphics.GetDevice()->CreateBuffer(&indexBufDesc, &indexData, &ib);
}

ID3D11Buffer* MeshComponent::VB()
{
	return vb;
}

ID3D11Buffer* MeshComponent::IB()
{
	return ib;
}

void MeshComponent::DestroyResources()
{
}

void MeshComponent::Draw()
{
}

void MeshComponent::Initialize()
{
}

void MeshComponent::Reload()
{
}

void MeshComponent::Update()
{
}
