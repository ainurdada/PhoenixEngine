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
#include "GBuffer.h"
#include "../../Lib/Math/Math.h"
#include "Light/LightManager.h"
#include "ConstantBuffer.h"

class Graphics
{
	struct ConstantData {
		SMath::Matrix InverseProjection;
		SMath::Matrix InverseView;
		SMath::Vector4 ViewerPosition;
		SMath::Vector4 ViewDirection;
		int screenResolution[2];
		float nearPlaneDistance;
		float fov;
	};
	struct PointLightData {
		SMath::Matrix viewProjection[6];
		SMath::Vector3 color;
		float intensity;
		SMath::Vector3 position;
		float attenuation_a;
		float attenuation_b;
		float attenuation_c;
	};
	struct GraphicSettings {
		int shadowResolution = 1024 * 2;
		int shadowCascadeCount = 1;
	};
public:
	HRESULT Init(const HWND& hWnd, int screenWidth, int screenHeight);
	const Microsoft::WRL::ComPtr<ID3D11Device>& GetDevice() const;
	ID3D11DeviceContext* GetContext() const;
	void SetUpIA(const Shader& shader);
	void SetShader(const Shader& shader);
	HRESULT SetUpRasterizer();
	void SetSolidRasterizer();
	void SetWireframeRasterizer();
	void SetShadowRasterizer();
	void SetUpViewPort(int width, int height);
	void UpdateState();
	void UpdateRenderTarget();
	GBuffer& GetGBuffer();
	void Output();
	void Present();
	void Cleanup();

	GraphicSettings settings;
	ID3D11SamplerState* pSampler;
	ID3D11SamplerState* shadowCompSampler;
	Vec4 backgroundColor;
private:
	const Shader* outputShader;
	IndexBuffer outputIb;
	GBuffer gBuffer;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3D11RasterizerState* solidRastState;
	ID3D11RasterizerState* wireframeRastState;
	ID3D11RasterizerState* shadowRastState;
	D3D11_VIEWPORT viewport = {};
	ConstantBuffer<PointLightData> point_light_data;
	ConstantBuffer<ConstantData> constant_data;
};