#pragma once
class Shader;

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
	friend class RenderComponent;
	friend class Graphics;
	friend class ShaderManager;
	friend class DebugLine;
public:
	Shader() {};
	~Shader();
private:
	HRESULT Compile(LPCWSTR shaderPath, Microsoft::WRL::ComPtr<ID3D11Device> device);

	ID3D11VertexShader* VS = nullptr;
	ID3D11PixelShader* PS = nullptr;
	ID3D11InputLayout* layout = nullptr; 
	LPCWSTR pathToShader = L"";
};

