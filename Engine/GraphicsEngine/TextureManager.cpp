#include "TextureManager.h"

#include <WICTextureLoader.h>
#include "../../App/Game.h"

std::unordered_map<LPCWSTR, ID3D11ShaderResourceView*> TextureManager::texture_map;

ID3D11ShaderResourceView* TextureManager::Get(LPCWSTR path)
{
	auto it = texture_map.find(path);
	if (it != texture_map.end())
	{
		return it->second;
	}

	HRESULT res;
	ID3D11ShaderResourceView* pTextureRV;
	res = DirectX::CreateWICTextureFromFile(
		Game::instance->graphics.GetDevice().Get(),
		Game::instance->graphics.GetContext(),
		path,
		nullptr,
		&pTextureRV
	);

	if (FAILED(res))
	{
		//error
	}

	texture_map.insert({ path, pTextureRV });
	return pTextureRV;
}
