#include "Shader.h"

#include <iostream>

HRESULT Shader::Compile(LPCWSTR pathToShader,
	D3D_SHADER_MACRO macros[],
	ID3DInclude* include)
{
	HRESULT res;
	res = D3DCompileFromFile(pathToShader,
		macros /*macros*/,
		include /*include*/,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR,
		0,
		&BC,
		&errorCode);

	// If the shader failed to compile it should have written something to the error message.
	if (errorCode) {
		char* compileErrors = (char*)(errorCode->GetBufferPointer());
		std::cout << compileErrors << std::endl;
		return NULL;
	}
	else
	{
		return res;
	}
}
