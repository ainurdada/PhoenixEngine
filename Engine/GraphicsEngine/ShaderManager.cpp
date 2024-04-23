#include "ShaderManager.h"
#include "../../App/Game.h"

using namespace std;
std::unordered_map<LPCWSTR, Shader*> ShaderManager::m_shaders;

const Shader* ShaderManager::Get(LPCWSTR path, UINT compileFlags)
{
	auto it = m_shaders.find(path);
	if (it != m_shaders.end())
	{
		return it->second;
	}

	HRESULT res;
	Shader* newShader = new Shader;
	res = newShader->Compile(path, Game::instance->graphics.GetDevice(), compileFlags);
	if (FAILED(res))
	{
		Game::instance->window.ShowMessageBox(newShader->pathToShader, L"Missing Shader File");
	}
	m_shaders.insert({ path, newShader });
	return newShader;
}
