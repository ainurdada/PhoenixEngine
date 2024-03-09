#include "LinearTexture.h"

#include "../../App/Game.h"

namespace Basic
{
	Texture* LinearTexture::Create(LPCWSTR path)
	{
		D3D11_SAMPLER_DESC sampDesc;
        ZeroMemory(&sampDesc, sizeof(sampDesc));
        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;      // Тип фильтрации - линейная
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;         // Задаем координаты
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        ID3D11SamplerState* sampState;
        HRESULT res = Game::instance->graphics.GetDevice()->CreateSamplerState(&sampDesc, &sampState);
        if (FAILED(res))
        {
            return nullptr;
        }
		Texture* tex = new Texture(path, sampState);
	}
}