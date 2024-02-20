#pragma once

#include "Shader.h"

#include <wrl.h>
#include <d3d11.h>
#include <d3d.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")


class Graphics
{
public:
	HRESULT Init(const HWND& hWnd, int screenWidth, int screenHeight);
	const Microsoft::WRL::ComPtr<ID3D11Device>& GetDevice() const;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	ID3D11RenderTargetView* rtv;
};


