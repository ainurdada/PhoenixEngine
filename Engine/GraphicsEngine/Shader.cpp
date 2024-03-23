#include "Shader.h"

#include <iostream>

Shader::~Shader()
{
	VS->Release();
	PS->Release();
	layout->Release();
}

HRESULT Shader::Compile(LPCWSTR shaderPath, Microsoft::WRL::ComPtr<ID3D11Device> device)
{
	pathToShader = shaderPath;
	HRESULT res;
	ID3DBlob* vertexBC = nullptr;
	ID3DBlob* errorVertexCode = nullptr;
	res = D3DCompileFromFile(pathToShader,
							 nullptr,
							 nullptr,
							 "VSMain",
							 "vs_5_0",
							 D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR,
							 0,
							 &vertexBC,
							 &errorVertexCode);

	// If the shader failed to compile it should have written something to the error message.
	if (errorVertexCode)
	{
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

	ID3DBlob* pixelBC = nullptr;
	ID3DBlob* errorPixelCode = nullptr;
	res = D3DCompileFromFile(pathToShader,
							 nullptr,
							 nullptr,
							 "PSMain",
							 "ps_5_0",
							 D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
							 0,
							 &pixelBC,
							 &errorPixelCode);

	// If the shader failed to compile it should have written something to the error message.
	if (errorPixelCode)
	{
		char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());
		std::cout << compileErrors << std::endl;
	}

	res = device->CreatePixelShader(
		pixelBC->GetBufferPointer(),
		pixelBC->GetBufferSize(),
		nullptr, &PS);

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
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			16,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
		D3D11_INPUT_ELEMENT_DESC {
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			32,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	layout = NULL;
	UINT nuElements = ARRAYSIZE(inputElements);
	res = device->CreateInputLayout(
		inputElements,
		nuElements,
		vertexBC->GetBufferPointer(),
		vertexBC->GetBufferSize(),
		&layout);
	return res;
}
