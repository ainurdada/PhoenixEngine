#pragma once
#include "Shader.h"
#include <wrl.h>
#include <unordered_map>

class ShaderManager
{
public:
	static const Shader* Get(LPCWSTR path);

private:
	static std::unordered_map<LPCWSTR, Shader*> m_shaders;
};

