#pragma once

#include <d3d11.h>

class Texture
{
	friend class RenderComponent;
public:
	Texture(LPCWSTR path, ID3D11SamplerState* sampler);
	Texture(LPCWSTR path);

private:
	ID3D11ShaderResourceView* pTextureRV = NULL;
	ID3D11SamplerState* pSampler = NULL;
};

