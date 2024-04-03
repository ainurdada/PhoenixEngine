#include "Mesh.h"
Mesh::Mesh(ID3D11Device* device, 
		   ID3D11DeviceContext* deviceContext, 
		   std::vector<Vertex>& verteces, 
		   std::vector<int>& indexes, 
		   std::vector<Texture>& textures, 
		   const DirectX::XMMATRIX& transformMatrix)
{
	this->deviceContext = deviceContext;
	this->textures = textures;
	this->transformMatrix = transformMatrix;

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
	this->textures = mesh.textures;
	this->transformMatrix = mesh.transformMatrix;
}

const DirectX::XMMATRIX& Mesh::GetTransformMatrix()
{
	return this->transformMatrix;
}

void Mesh::Draw()
{
	UINT offset = 0;

	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i].GetType() == aiTextureType_DIFFUSE)
		{
			deviceContext->PSSetShaderResources(0, 1, textures[i].GetTextureResourceViewAddress());
			break;
		}
	}

	deviceContext->IASetVertexBuffers(0, 1, vb.GetAddressOf(), vb.StridePtr(), &offset);
	deviceContext->IASetIndexBuffer(ib.Get(), DXGI_FORMAT_R32_UINT, 0);
	deviceContext->DrawIndexed(ib.IndexCount(), 0, 0);
}

void Mesh::DrawShadow()
{
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, vb.GetAddressOf(), vb.StridePtr(), &offset);
	deviceContext->IASetIndexBuffer(ib.Get(), DXGI_FORMAT_R32_UINT, 0);
	deviceContext->DrawIndexed(ib.IndexCount(), 0, 0);
}
