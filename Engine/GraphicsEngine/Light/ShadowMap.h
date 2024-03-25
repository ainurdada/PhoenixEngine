#pragma once

#include <d3d11.h>

class ShadowMap
{
public:
	void Initialize();
private:
	ID3D11Texture2D* shadowTexArr;
	ID3D11DepthStencilView* depthDSV;
	ID3D11ShaderResourceView* depthSRV;
};

