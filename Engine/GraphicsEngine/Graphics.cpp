#include "Graphics.h"

#include "iostream"

using namespace std;

HRESULT Graphics::Init(const HWND& hWnd, int screenWidth, int screenHeight)
{
	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
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

	auto res = D3D11CreateDeviceAndSwapChain(
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

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.Width = screenWidth;
	depthStencilDesc.Height = screenHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
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

	//Set our Render Target
	context->OMSetRenderTargets(1, &rtv, depthStencilView);


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
void Graphics::SetUpIA(ID3D11InputLayout* layout, Mesh& mesh, Shader& shader)
{
	context->IASetInputLayout(layout);
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetIndexBuffer(mesh.ib, DXGI_FORMAT_R32_UINT, 0);
	vb = mesh.vb;
	context->IASetVertexBuffers(0, 1, &vb, strides, offsets);
}

void Graphics::SetShader(const Shader& shader)
{
	context->VSSetShader(shader.VS, nullptr, 0);
	context->PSSetShader(shader.PS, nullptr, 0);
}

HRESULT Graphics::SetUpRasterizer()
{
	rastDesc.CullMode = D3D11_CULL_BACK;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	HRESULT res;
	res = device->CreateRasterizerState(&rastDesc, &rastState);

	context->RSSetState(rastState);

	return res;
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
	context->RSSetState(rastState);
}

void Graphics::UpdateRenderTarget()
{
	context->OMSetRenderTargets(1, &rtv, depthStencilView);
	float color[4] = { backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f };
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
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
