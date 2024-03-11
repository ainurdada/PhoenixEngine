#include "Mesh.h"
Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<Vertex>& verteces, std::vector<int>& indexes)
{
	this->deviceContext = deviceContext;
	
	HRESULT res = vb.Initialize(device, verteces.data(), verteces.size());
	if (FAILED(res))
	{
		// error
	}

	res = ib.Initialize(device, indexes.data(), indexes.size());
	if (FAILED(res))
	{
		// error
	}
}

Mesh::Mesh(const Mesh& mesh)
{
	this->deviceContext = mesh.deviceContext;
	this->vb = mesh.vb;
	this->ib = mesh.ib;
}

void Mesh::Draw()
{
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, vb.GetAddressOf(), vb.StridePtr(), &offset);
	deviceContext->IASetIndexBuffer(ib.Get(), DXGI_FORMAT_R32_UINT, 0);
	deviceContext->DrawIndexed(ib.BufferSize(), 0, 0);
}
