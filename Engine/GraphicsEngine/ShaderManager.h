#pragma once
#include "Shader.h"
#include <wrl.h>
#include <unordered_map>

class ShaderManager
{
public:
	static const Shader* Get(LPCWSTR path, UINT compileFlags = Shader::FLAG_PS | Shader::FLAG_VS);

private:
	static std::unordered_map<LPCWSTR, Shader*> m_shaders;
};

