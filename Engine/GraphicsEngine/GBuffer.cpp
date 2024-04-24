#include "GBuffer.h"

#include "ShaderManager.h"

void GBuffer::Initialize(ID3D11Device* device, int screenWidth, int screenHeigt, LPCWSTR shaderPath)
{
	shader = ShaderManager::Get(shaderPath);
#pragma region Diffuse
	{
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

		D3D11_SHADER_RESOURCE_VIEW_DESC diffuseSRVDesc = {};
		diffuseSRVDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		diffuseSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		diffuseSRVDesc.Texture2DArray.MostDetailedMip = 0;
		diffuseSRVDesc.Texture2DArray.MipLevels = 1;
		diffuseSRVDesc.Texture2DArray.FirstArraySlice = 0;
		device->CreateShaderResourceView(diffuseTexture, &diffuseSRVDesc, &srvs.diffuseSRV);
	}
#pragma endregion

#pragma region Normal
	{
		ID3D11Texture2D* normalTexture;
		D3D11_TEXTURE2D_DESC normalTextureDesc = {};
		normalTextureDesc.Width = screenWidth;
		normalTextureDesc.Height = screenHeigt;
		normalTextureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		normalTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		normalTextureDesc.Usage = D3D11_USAGE_DEFAULT;
		normalTextureDesc.MipLevels = 1;
		normalTextureDesc.ArraySize = 1;
		normalTextureDesc.SampleDesc.Count = 1;
		normalTextureDesc.SampleDesc.Quality = 0;
		normalTextureDesc.CPUAccessFlags = 0;
		normalTextureDesc.MiscFlags = 0;
		device->CreateTexture2D(&normalTextureDesc, nullptr, &normalTexture);
		device->CreateRenderTargetView(normalTexture, nullptr, &rtvs.normalRTV);

		D3D11_SHADER_RESOURCE_VIEW_DESC normalSRVDesc = {};
		normalSRVDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		normalSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		normalSRVDesc.Texture2DArray.MostDetailedMip = 0;
		normalSRVDesc.Texture2DArray.MipLevels = 1;
		normalSRVDesc.Texture2DArray.FirstArraySlice = 0;
		device->CreateShaderResourceView(normalTexture, &normalSRVDesc, &srvs.normalSRV);
	}
#pragma endregion

#pragma region Depth
	{
		ID3D11Texture2D* depthTexture;
		D3D11_TEXTURE2D_DESC depthTextureDesc = {};
		depthTextureDesc.Width = screenWidth;
		depthTextureDesc.Height = screenHeigt;
		depthTextureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		depthTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
		depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTextureDesc.MipLevels = 1;
		depthTextureDesc.ArraySize = 1;
		depthTextureDesc.SampleDesc.Count = 1;
		depthTextureDesc.SampleDesc.Quality = 0;
		depthTextureDesc.CPUAccessFlags = 0;
		depthTextureDesc.MiscFlags = 0;
		device->CreateTexture2D(&depthTextureDesc, nullptr, &depthTexture);

		D3D11_DEPTH_STENCIL_VIEW_DESC diffuseDSVDesc = {};
		diffuseDSVDesc.Format = DXGI_FORMAT_D32_FLOAT;
		diffuseDSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		diffuseDSVDesc.Texture2D.MipSlice = 0;
		device->CreateDepthStencilView(depthTexture, &diffuseDSVDesc, &dsv);

		D3D11_SHADER_RESOURCE_VIEW_DESC depthSRVDesc = {};
		depthSRVDesc.Format = DXGI_FORMAT_R32_FLOAT;
		depthSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		depthSRVDesc.Texture2DArray.MostDetailedMip = 0;
		depthSRVDesc.Texture2DArray.MipLevels = 1;
		depthSRVDesc.Texture2DArray.FirstArraySlice = 0;
		device->CreateShaderResourceView(depthTexture, &depthSRVDesc, &srvs.depthSRV);
	}
#pragma endregion
}


void GBuffer::SetRenderTargets(ID3D11DeviceContext* context)
{
	context->OMSetRenderTargets(2, &rtvs.diffuseRTV, dsv);
	float color[4] = { 0,0,0,1 };
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->ClearRenderTargetView(rtvs.diffuseRTV, color);
	context->ClearRenderTargetView(rtvs.normalRTV, color);
}

void GBuffer::PrepareToDrawObject(ID3D11DeviceContext* context)
{
	context->IASetInputLayout(shader->layout);
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->VSSetShader(shader->VS, nullptr, 0);
	context->PSSetShader(shader->PS, nullptr, 0);
}

GBuffer::GBufferSRVs& GBuffer::GetSRVs()
{
	return srvs;
}
