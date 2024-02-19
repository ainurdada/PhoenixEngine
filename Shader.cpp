#include "Shader.h"

#include <iostream>

HRESULT Shader::Compile(LPCWSTR pathToShader,
	D3D_SHADER_MACRO macros[],
	ID3DInclude* include,
	LPCSTR entryPoint,
	LPCSTR target,
	UINT flags1,
	UINT flags2)
{
	HRESULT res;
	res = D3DCompileFromFile(pathToShader,
		macros /*macros*/,
		include /*include*/,
		entryPoint,
		target,
		flags1,
		flags2,
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
