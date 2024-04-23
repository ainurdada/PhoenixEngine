#pragma once

#include <d3d11.h>
#include "Shader.h"


class GBuffer
{
	struct GBufferRTVs {
		ID3D11RenderTargetView* diffuseRTV;
		ID3D11RenderTargetView* normalRTV;
		ID3D11RenderTargetView* specularRTV;
		ID3D11RenderTargetView* depthRTV;
		const int count = 4;
	};

	struct GBufferSRVs
	{
		ID3D11ShaderResourceView* diffuseSRV;
		ID3D11ShaderResourceView* normalSRV;
		ID3D11ShaderResourceView* specularSRV;
		ID3D11ShaderResourceView* depthSRV;
		const int count = 4;
	};

public:
	void Initialize(ID3D11Device* device, int screenWidth, int screenHeigt, LPCWSTR shaderPath);
	void SetRenderTargets(ID3D11DeviceContext* context);
	GBufferSRVs GetSRVs();
private:
	const Shader* shader;

	GBufferRTVs rtvs;
	GBufferSRVs srvs;

	ID3D11DepthStencilView* diffuseDSV;
};

