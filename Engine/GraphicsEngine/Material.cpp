#include "Material.h"
#include "ShaderManager.h"

void Material::Init()
{
	shader = ShaderManager::Get(shaderPath);
}
