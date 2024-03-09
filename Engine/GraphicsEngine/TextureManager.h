#pragma once

#include <unordered_map>
#include <wrl.h>
#include "d3d11.h"

class TextureManager
{
public:
	static ID3D11ShaderResourceView* Get(LPCWSTR path);

private:
	static std::unordered_map<LPCWSTR, ID3D11ShaderResourceView*> texture_map;
};

