#include "GBuffer.h"

#include "ShaderManager.h"

void GBuffer::Initialize(ID3D11Device* device, int screenWidth, int screenHeigt, LPCWSTR shaderPath)
{
	shader = ShaderManager::Get(shaderPath);
#pragma region Diffuse
	ID3D11Texture2D* diffuseTexture;
	D3D11_TEXTURE2D_DESC diffuseTextureDesc = {};
	diffuseTextureDesc.Width = screenWidth;
	diffuseTextureDesc.Height = screenHeigt;
	diffuseTextureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	diffuseTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	diffuseTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	diffuseTextureDesc.MipLevels = 1;
	diffuseTextureDesc.ArraySize = 1;
	diffuseTextureDesc.SampleDesc.Count = 1;
	diffuseTextureDesc.SampleDesc.Quality = 0;
	diffuseTextureDesc.CPUAccessFlags = 0;
	diffuseTextureDesc.MiscFlags = 0;
	device->CreateTexture2D(&diffuseTextureDesc, nullptr, &diffuseTexture);
	device->CreateRenderTargetView(diffuseTexture, nullptr, &rtvs.diffuseRTV);

	ID3D11Texture2D* diffuseDSVTexture;
	D3D11_TEXTURE2D_DESC diffuseDSVTextureDesc = diffuseTextureDesc;
	diffuseDSVTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
	diffuseDSVTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	device->CreateTexture2D(&diffuseDSVTextureDesc, nullptr, &diffuseDSVTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC diffuseDSVDesc = {};
	diffuseDSVDesc.Format = DXGI_FORMAT_D32_FLOAT;
	diffuseDSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	diffuseDSVDesc.Texture2D.MipSlice = 0;
	device->CreateDepthStencilView(diffuseDSVTexture, &diffuseDSVDesc, &diffuseDSV);

	D3D11_SHADER_RESOURCE_VIEW_DESC diffuseSRVDesc = {};
	diffuseSRVDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	diffuseSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	diffuseSRVDesc.Texture2DArray.MostDetailedMip = 0;
	diffuseSRVDesc.Texture2DArray.MipLevels = 1;
	diffuseSRVDesc.Texture2DArray.FirstArraySlice = 0;
	device->CreateShaderResourceView(diffuseTexture, &diffuseSRVDesc, &srvs.diffuseSRV);
#pragma endregion
}


void GBuffer::SetRenderTargets(ID3D11DeviceContext* context)
{
	context->OMSetRenderTargets(1, &rtvs.diffuseRTV, diffuseDSV);
	float color[4] = { 0,0,0,1 };
	context->ClearDepthStencilView(diffuseDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->ClearRenderTargetView(rtvs.diffuseRTV, color);
}

void GBuffer::PrepareToDrawObject(ID3D11DeviceContext* context)
{
	context->IASetInputLayout(shader->layout);
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->VSSetShader(shader->VS, nullptr, 0);
	context->PSSetShader(shader->PS, nullptr, 0);
}

GBuffer::GBufferSRVs GBuffer::GetSRVs()
{
	return srvs;
}
