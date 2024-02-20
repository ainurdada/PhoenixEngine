#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <d3d.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

class Shader
{
public:
	Shader(LPCWSTR pathToShader, const Microsoft::WRL::ComPtr<ID3D11Device>& device);
public:
	HRESULT CompileVS(D3D_SHADER_MACRO macros[], ID3DInclude* include);
	HRESULT CompilePS(D3D_SHADER_MACRO macros[], ID3DInclude* include);
	HRESULT CreateInputLayout();
private:
	ID3DBlob* vertexBC = nullptr;
	ID3DBlob* pixelBC = nullptr;
	ID3DBlob* errorVertexCode = nullptr;
	ID3DBlob* errorPixelCode = nullptr;
	ID3D11VertexShader* VS = nullptr;
	ID3D11PixelShader* PS = nullptr; 
	ID3D11InputLayout* layout = nullptr; 
	LPCWSTR pathToShader;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
};

