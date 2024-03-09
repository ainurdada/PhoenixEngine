#include "Texture.h"

#include "TextureManager.h"
#include "../../App/Game.h"

Texture::Texture(LPCWSTR path, ID3D11SamplerState* sampler)
{
	pTextureRV = TextureManager::Get(path);
	pSampler = sampler;
}

Texture::Texture(LPCWSTR path)
{
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* sampler;
	HRESULT res = Game::instance->graphics.GetDevice()->CreateSamplerState(&sampDesc, &sampler);
	if (FAILED(res))
	{
		//error
	}

	pTextureRV = TextureManager::Get(path);
	pSampler = sampler;
}
