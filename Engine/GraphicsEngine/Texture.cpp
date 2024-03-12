#include "Texture.h"

#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>

#include "TextureManager.h"
#include "../../App/Game.h"
#include "../../Lib/Tools/StringHelper.h"
#include "../../Basic/Constants/Colors.h"

Texture::Texture(ID3D11Device* device, const SMath::Color& color, aiTextureType type)
{
	this->Initialize1x1ColorTexture(device, color, type);
}

Texture::Texture(ID3D11Device* device, const SMath::Color* colorData, UINT width, UINT height, aiTextureType type)
{
	this->InitializeColorTexture(device, colorData, width, height, type);
}

Texture::Texture(ID3D11Device* device, const std::string& filePath, aiTextureType type)
{
	this->type = type;
	HRESULT res;
	if (StringHelper::GetFileExtention(filePath) == ".dds")
	{
		res = DirectX::CreateDDSTextureFromFile(device, StringHelper::StringToWide(filePath).c_str(), this->texture.GetAddressOf(), this->textureView.GetAddressOf());
		if (FAILED(res))
		{
			this->Initialize1x1ColorTexture(device, Basic::UnloadedTextureColor, type);
		}
		return;
	}
	else
	{
		res = DirectX::CreateWICTextureFromFile(device, StringHelper::StringToWide(filePath).c_str(), this->texture.GetAddressOf(), this->textureView.GetAddressOf());
		if (FAILED(res))
		{
			this->Initialize1x1ColorTexture(device, Basic::UnloadedTextureColor, type);
		}
		return;
	}
}

aiTextureType Texture::GetType()
{
	return this->type;
}

ID3D11ShaderResourceView* Texture::GetTextureResourceView()
{
	return this->textureView.Get();
}

ID3D11ShaderResourceView** Texture::GetTextureResourceViewAddress()
{
	return this->textureView.GetAddressOf();
}

void Texture::Initialize1x1ColorTexture(ID3D11Device* device, const SMath::Color& colorData, aiTextureType type)
{
	this->InitializeColorTexture(device, &colorData, 1, 1, type);
}

void Texture::InitializeColorTexture(ID3D11Device* device, const SMath::Color* colorData, UINT width, UINT height, aiTextureType type)
{
	this->type = type;
	CD3D11_TEXTURE2D_DESC textDesc(DXGI_FORMAT_R32G32B32A32_FLOAT, width, height);
	ID3D11Texture2D* p2DTexture = nullptr;
	D3D11_SUBRESOURCE_DATA initialData{};
	initialData.pSysMem = colorData;
	initialData.SysMemPitch = width * sizeof(SMath::Color);
	HRESULT res = device->CreateTexture2D(&textDesc, &initialData, &p2DTexture);
	if (FAILED(res))
	{
		// error
	}
	texture = static_cast<ID3D11Texture2D*>(p2DTexture);
	CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textDesc.Format);
	res = device->CreateShaderResourceView(texture.Get(), &srvDesc, textureView.GetAddressOf());
	if (FAILED(res))
	{
		// error
	}
}
