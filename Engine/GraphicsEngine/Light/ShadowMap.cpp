#include "ShadowMap.h"

#include "../../App/Game.h"
#include "../ShaderManager.h"
#include "../../FileManager/BaseResources.h"

void ShadowMap::Initialize(LightCamera* lightCamera)
{
	this->light_camera = lightCamera;

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

	ID3D11Texture2D* shadowTexArr;
	HRESULT res = Game::instance->graphics.GetDevice()->CreateTexture2D(&shadowMaplDesc, NULL, &shadowTexArr);

	if (FAILED(res))
	{
		// error
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dViewDesc = {};
	ZeroMemory(&dViewDesc, sizeof(dViewDesc));
	dViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
	dViewDesc.Texture2DArray.MipSlice = 0;
	dViewDesc.Texture2DArray.FirstArraySlice = 0;
	dViewDesc.Texture2DArray.ArraySize = Game::instance->graphics.settings.shadowCascadeCount;
	res = Game::instance->graphics.GetDevice()->CreateDepthStencilView(shadowTexArr, &dViewDesc, &depthDSV);

	if (FAILED(res))
	{
		// error
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Texture2DArray.MostDetailedMip = 0;
	srvDesc.Texture2DArray.MipLevels = 1;
	srvDesc.Texture2DArray.FirstArraySlice = 0;
	srvDesc.Texture2DArray.ArraySize = Game::instance->graphics.settings.shadowCascadeCount;
	res = Game::instance->graphics.GetDevice()->CreateShaderResourceView(shadowTexArr, &srvDesc, &depthSRV);

	if (FAILED(res))
	{
		// error
	}

	shadowShader = ShaderManager::Get(BaseResource::shadowShader);
}

void ShadowMap::Generate(GameObject gameObjects[], int count)
{
	Game::instance->graphics.SetUpViewPort(Game::instance->graphics.settings.shadowResolution, Game::instance->graphics.settings.shadowResolution);
	Game::instance->graphics.GetContext()->OMSetRenderTargets(0, nullptr, depthDSV);
	Game::instance->graphics.GetContext()->ClearDepthStencilView(depthDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	Game::instance->graphics.SetSolidRasterizer();

	// Set shader
	Game::instance->graphics.SetUpIA(*shadowShader);
	Game::instance->graphics.SetShader(*shadowShader);

	//Game::instance->graphics.GetContext()->VSSetShaderResources(0, 1, &depthSRV);

	for (int i = 0; i < count; i++)
	{
		gameObjects[i].DrawShadow(light_camera);
	}
}
