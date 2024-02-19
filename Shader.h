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
	HRESULT Compile(LPCWSTR pathToShader,
		D3D_SHADER_MACRO macros[],
		ID3DInclude* include,
		LPCSTR entryPoint,
		LPCSTR target,
		UINT flags1,
		UINT flags2);
private:
	ID3DBlob* BC = nullptr;
	ID3DBlob* errorCode = nullptr;
};

