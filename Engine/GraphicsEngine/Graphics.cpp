#include "Graphics.h"

#include "iostream"
#include "ShaderManager.h"
#include "../FileManager/BaseResources.h"

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

	gBuffer.Initialize(device.Get(), screenWidth, screenHeight, BaseResource::gBufferShader);

	outputShader = ShaderManager::Get(BaseResource::screenQuadShader);
	int indexes[] = { 0,1,2,2,1,3 };
	outputIb.Initialize(device.Get(), indexes, 6);

	constant_data.Initialize(device.Get(), context);
	point_light_data.Initialize(device.Get(), context);

	ID3D11Texture2D* backTex;
	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex);	// __uuidof(ID3D11Texture2D)
	res = device->CreateRenderTargetView(backTex, nullptr, &rtv);

	if (FAILED(res))
	{
		cout << "failed to create RenderTargetView" << endl;
	}

	D3D11_SAMPLER_DESC sampDesc{};
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;      // Тип фильтрации
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampDesc.MipLODBias = 0;
	sampDesc.BorderColor[0] = 0.0f;
	sampDesc.BorderColor[1] = 0.0f;
	sampDesc.BorderColor[2] = 0.0f;
	sampDesc.BorderColor[3] = 0.0f;
	sampDesc.MaxAnisotropy = 1;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	res = device->CreateSamplerState(&sampDesc, &pSampler);
	if (FAILED(res))
	{
		cout << "failed to create SamplerState" << endl;
	}

	sampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	//sampDesc.MaxAnisotropy = 0;

	res = device->CreateSamplerState(&sampDesc, &shadowCompSampler);
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

	rastDesc.CullMode = D3D11_CULL_BACK;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.DepthClipEnable = true;
	rastDesc.DepthBias = 10;
	rastDesc.DepthBiasClamp = 0.0f;
	rastDesc.SlopeScaledDepthBias = 4.f;
	res = device->CreateRasterizerState(&rastDesc, &shadowRastState);

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

void Graphics::SetShadowRasterizer()
{
	context->RSSetState(shadowRastState);
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

GBuffer& Graphics::GetGBuffer()
{
	return gBuffer;
}


#include "../../App/Game.h"
void Graphics::Output()
{
	SetUpIA(*outputShader);
	SetShader(*outputShader);
	context->OMSetRenderTargets(1, &rtv, nullptr);
	float color[4] = { backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f };
	context->ClearRenderTargetView(rtv, color);

	context->PSSetSamplers(0, 1, &shadowCompSampler);

	// constant buffer
	SMath::Matrix cameraView = Game::instance->mainCamera->ViewMatrix();
	cameraView = DirectX::XMMatrixInverse(nullptr, cameraView);
	SMath::Matrix cameraProjection = Game::instance->mainCamera->ProjectionMatrix();
	cameraProjection = DirectX::XMMatrixInverse(nullptr, cameraProjection);
	SMath::Matrix VP = DirectX::XMMatrixTranspose(
		//cameraView
		cameraProjection 
	);
	constant_data.data.InverseProjection = DirectX::XMMatrixTranspose(cameraProjection);
	constant_data.data.InverseView = DirectX::XMMatrixTranspose(cameraView);
	constant_data.data.ViewerPosition = SMath::Vector4(Game::instance->mainCamera->transform.position());
	constant_data.data.ViewDirection = SMath::Vector4(Game::instance->mainCamera->transform.Forward());
	constant_data.data.screenResolution[0] = Game::instance->window.ClientWidth;
	constant_data.data.screenResolution[1] = Game::instance->window.ClientHeight;
	constant_data.data.nearPlaneDistance = Game::instance->mainCamera->minClipDistance();
	constant_data.data.fov = Game::instance->mainCamera->fov() * DEG_TO_RAD;
	constant_data.ApplyChanges();
	Game::instance->graphics.GetContext()->PSSetConstantBuffers(0, 1, constant_data.GetAddressOf());

	// point light buffer
	if (Game::instance->pointLights.size() != 0)
	{
		for (int i = 0; i < 6; i++) {
			point_light_data.data.viewProjection[i] = Game::instance->pointLights[0]->GetCameras()[i].ViewProjectionMatrix();
		}
		point_light_data.data.position = Game::instance->pointLights[0]->gameObject->transform.position();
		point_light_data.data.intensity = Game::instance->pointLights[0]->intensity;
		point_light_data.data.color = Game::instance->pointLights[0]->color;
		point_light_data.data.attenuation_a = Game::instance->pointLights[0]->attenuation_a;
		point_light_data.data.attenuation_b = Game::instance->pointLights[0]->attenuation_b;
		point_light_data.data.attenuation_c = Game::instance->pointLights[0]->attenuation_c;
		point_light_data.ApplyChanges();
		//Game::instance->graphics.GetContext()->PSSetShaderResources(1, 6, Game::instance->pointLights[0]->GetShadowMapsResourceAdresses().data());
	}
	Game::instance->graphics.GetContext()->PSSetConstantBuffers(1, 1, point_light_data.GetAddressOf());

	context->PSSetShaderResources(0, gBuffer.GetSRVs().count, &gBuffer.GetSRVs().diffuseSRV);
	context->PSSetShaderResources(gBuffer.GetSRVs().count, 6, Game::instance->pointLights[0]->GetShadowMapsResourceAdresses().data());
	context->IASetIndexBuffer(outputIb.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(outputIb.IndexCount(), 0, 0);
}

void Graphics::Present()
{
	swapChain->Present(0, 0);
}

void Graphics::Cleanup()
{
	if (context) context->ClearState();
	if (rtv) rtv->Release();
	if (swapChain) swapChain->Release();
	if (context) context->Release();
	if (device) device->Release();
}
