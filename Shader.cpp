#include "Shader.h"

#include <iostream>

Shader::~Shader()
{
	VS->Release();
	PS->Release();
}

HRESULT Shader::CompileVS(D3D_SHADER_MACRO macros[], ID3DInclude* include)
{
	HRESULT res;
	res = D3DCompileFromFile(pathToShader,
		macros /*macros*/,
		include /*include*/,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR,
		0,
		&vertexBC,
		&errorVertexCode);

	// If the shader failed to compile it should have written something to the error message.
	if (errorVertexCode) {
		char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());
		std::cout << compileErrors << std::endl;
	}
	else if (FAILED(res)) 
	{
		return res;
	}

	res = device->CreateVertexShader(
		vertexBC->GetBufferPointer(),
		vertexBC->GetBufferSize(),
		nullptr, &VS);
	return res;
}

HRESULT Shader::CompilePS(D3D_SHADER_MACRO macros[], ID3DInclude* include)
{
	HRESULT res;
	res = D3DCompileFromFile(pathToShader,
		macros /*macros*/,
		include /*include*/,
		"PSMain",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pixelBC,
		&errorPixelCode);

	// If the shader failed to compile it should have written something to the error message.
	if (errorPixelCode) {
		char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());
		std::cout << compileErrors << std::endl;
	}

	res = device->CreatePixelShader(
		pixelBC->GetBufferPointer(),
		pixelBC->GetBufferSize(),
		nullptr, &PS);
	return res;
}

HRESULT Shader::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	HRESULT res;
	res = device->CreateInputLayout(
		inputElements,
		2,
		vertexBC->GetBufferPointer(),
		vertexBC->GetBufferSize(),
		&layout);
	return res;
}
