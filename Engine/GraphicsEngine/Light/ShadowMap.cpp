#include "ShadowMap.h"

#include "../../App/Game.h"

void ShadowMap::Initialize()
{
	D3D11_TEXTURE2D_DESC shadowMaplDesc;
	ZeroMemory(&shadowMaplDesc, sizeof(shadowMaplDesc));
	shadowMaplDesc.Width = Game::instance->graphics.settings.shadowResolution;
	shadowMaplDesc.Height = Game::instance->graphics.settings.shadowResolution;
	shadowMaplDesc.ArraySize = Game::instance->graphics.settings.shadowCascadeCount;
	shadowMaplDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
	shadowMaplDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	shadowMaplDesc.MipLevels = 1;
	shadowMaplDesc.SampleDesc.Count = 1;
	shadowMaplDesc.SampleDesc.Quality = 0;
	shadowMaplDesc.Usage = D3D11_USAGE_DEFAULT;
	shadowMaplDesc.CPUAccessFlags = 0;
	shadowMaplDesc.MiscFlags = 0;
	HRESULT res = Game::instance->graphics.GetDevice()->CreateTexture2D(&shadowMaplDesc, NULL, &shadowTexArr);

	D3D11_DEPTH_STENCIL_VIEW_DESC dViewDesc = {};
	ZeroMemory(&dViewDesc, sizeof(dViewDesc));
	dViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
	dViewDesc.Texture2DArray.MipSlice = 0;
	dViewDesc.Texture2DArray.FirstArraySlice = 0;
	dViewDesc.Texture2DArray.ArraySize = 4;
	res = Game::instance->graphics.GetDevice()->CreateDepthStencilView(shadowTexArr, &dViewDesc, &depthDSV);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Texture2DArray.MostDetailedMip = 0;
	srvDesc.Texture2DArray.MipLevels = 1;
	srvDesc.Texture2DArray.FirstArraySlice = 0;
	srvDesc.Texture2DArray.ArraySize = 4;
	res = res = Game::instance->graphics.GetDevice()->CreateShaderResourceView(shadowTexArr, &srvDesc, &depthSRV);
}
