#include "Graphics.h"

#include "iostream"

using namespace std;

HRESULT Graphics::Init(const HWND& hWnd, int screenWidth, int screenHeight)
{
	HRESULT res;

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	ZeroMemory(&swapDesc, sizeof(swapDesc));
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = screenWidth;
	swapDesc.BufferDesc.Height = screenHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&swapChain,
		&device,
		nullptr,
		&context);

	if (FAILED(res))
	{
		cout << "failed to create DeviceAndSwapChain" << endl;
	}

	ID3D11Texture2D* backTex;
	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex);	// __uuidof(ID3D11Texture2D)
	res = device->CreateRenderTargetView(backTex, nullptr, &rtv);

	if (FAILED(res))
	{
		cout << "failed to create RenderTargetView" << endl;
	}

	// shadow rtv
	D3D11_TEXTURE2D_DESC shadow_texture_descriptor{};
	shadow_texture_descriptor.Width = settings.shadowResolution;
	shadow_texture_descriptor.Height = settings.shadowResolution;
	shadow_texture_descriptor.MipLevels = 1;
	shadow_texture_descriptor.ArraySize = 1;
	shadow_texture_descriptor.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	shadow_texture_descriptor.SampleDesc.Count = 1;
	shadow_texture_descriptor.Usage = D3D11_USAGE_DEFAULT;
	shadow_texture_descriptor.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	ID3D11Texture2D* shadow_texture;
	device->CreateTexture2D(&shadow_texture_descriptor, nullptr, &shadow_texture);
	device->CreateRenderTargetView(shadow_texture, nullptr, &rtv_shadow);
	device->CreateShaderResourceView(shadow_texture, nullptr, &resource_shadow);

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.Width = screenWidth;
	depthStencilDesc.Height = screenHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	//Create the Depth/Stencil View
	res = device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = depthStencilDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	res = device->CreateDepthStencilView(depthStencilBuffer, &dsvDesc, &depthStencilView);

	if (FAILED(res))
	{
		cout << "failed to create DepthStencilView" << endl;
	}

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;      // Тип фильтрации
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;         // Задаем координаты
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	res = device->CreateSamplerState(&sampDesc, &pSampler);
	if (FAILED(res))
	{
		cout << "failed to create SamplerState" << endl;
	}

	return res;
}

const Microsoft::WRL::ComPtr<ID3D11Device>& Graphics::GetDevice() const
{
	return device;
}

ID3D11DeviceContext* Graphics::GetContext() const
{
	return context;
}

UINT strides[] = { 32 };
UINT offsets[] = { 0 };

ID3D11Buffer* vb;
void Graphics::SetUpIA(const Shader& shader)
{
	context->IASetInputLayout(shader.layout);
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Graphics::SetShader(const Shader& shader)
{
	context->VSSetShader(shader.VS, nullptr, 0);
	context->PSSetShader(shader.PS, nullptr, 0);
}

HRESULT Graphics::SetUpRasterizer()
{
	HRESULT res;

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_BACK;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	res = device->CreateRasterizerState(&rastDesc, &solidRastState);

	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_WIREFRAME;
	res = device->CreateRasterizerState(&rastDesc, &wireframeRastState);

	context->RSSetState(solidRastState);

	return res;
}

void Graphics::SetSolidRasterizer()
{
	context->RSSetState(solidRastState);
}

void Graphics::SetWireframeRasterizer()
{
	context->RSSetState(wireframeRastState);
}

void Graphics::SetUpViewPort(int width, int height)
{
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);
}

void Graphics::UpdateState()
{
	context->ClearState();
	context->RSSetState(solidRastState);
}

void Graphics::UpdateRenderTarget()
{
}

void Graphics::SetShadowDrawMode()
{
	float color[4] = { 0.f,0.f,0.f,0.f };
	context->ClearRenderTargetView(rtv_shadow, color);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv_shadow, depthStencilView);
}

void Graphics::SetObjectDrawMode()
{
	context->OMSetRenderTargets(1, &rtv, depthStencilView);
	float color[4] = { backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f };
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->ClearRenderTargetView(rtv, color);
}

void Graphics::Present()
{
	swapChain->Present(0, 0);
}

void Graphics::Cleanup()
{
	if (context) context->ClearState();
	if (depthStencilBuffer) depthStencilBuffer->Release();
	if (depthStencilView) depthStencilView->Release();
	if (rtv) rtv->Release();
	if (swapChain) swapChain->Release();
	if (context) context->Release();
	if (device) device->Release();
}
