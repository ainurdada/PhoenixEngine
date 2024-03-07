#pragma once
class Graphics;

#include <wrl.h>
#include <d3d11.h>
#include <d3d.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include "Mesh.h"
#include "Shader.h"
#include "../../Lib/Math/Math.h"

class Graphics
{
public:
	HRESULT Init(const HWND& hWnd, int screenWidth, int screenHeight);
	const Microsoft::WRL::ComPtr<ID3D11Device>& GetDevice() const;
	ID3D11DeviceContext* GetContext() const;
	void SetUpIA(const Mesh& mesh, const Shader& shader);
	void SetShader(const Shader& shader);
	HRESULT SetUpRasterizer();
	void SetUpViewPort(int width, int height);
	void UpdateState();
	void UpdateRenderTarget();
	void Present();
	void Cleanup();

	Vec4 backgroundColor;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	ID3D11RenderTargetView* rtv;
	CD3D11_RASTERIZER_DESC rastDesc = {};
	ID3D11RasterizerState* rastState;
	D3D11_VIEWPORT viewport = {};
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
};