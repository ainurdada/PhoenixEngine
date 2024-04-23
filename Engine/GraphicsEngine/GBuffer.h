#pragma once

#include <d3d11.h>
#include "Shader.h"


class GBuffer
{
public:
	void Initialize(ID3D11Device* device, int screenWidth, int screenHeigt, LPCWSTR shaderPath);
	void SetRenderTargets(ID3D11DeviceContext* context);
private:
	const Shader* shader;

	ID3D11RenderTargetView* diffuseRTV;
	ID3D11RenderTargetView* normalRTV;
	ID3D11RenderTargetView* specularRTV;
	ID3D11RenderTargetView* depthRTV;

	ID3D11ShaderResourceView* diffuseSRV;
	ID3D11ShaderResourceView* normalSRV;
	ID3D11ShaderResourceView* specularSRV;
	ID3D11ShaderResourceView* depthSRV;

	ID3D11DepthStencilView* diffuseDSV;
};

