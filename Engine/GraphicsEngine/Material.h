#pragma once

#include "Shader.h"
#include "Texture.h"

class Material
{
	friend class RenderComponent;
public:
	Texture* texture;
	LPCWSTR shaderPath;

private:
	void Init();

	const Shader* shader;
};

