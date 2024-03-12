#include "RenderComponent.h"
#include "../../GraphicsEngine/ShaderManager.h"
#include "../../../App/Game.h"

void RenderComponent::DestroyResources()
{
	transform_buffer->Release();
}

#include "iostream"
using namespace DirectX;
void RenderComponent::Draw()
{
	// Set shader
	Game::instance->graphics.SetUpIA(*shader);
	Game::instance->graphics.SetShader(*shader);
	Game::instance->graphics.GetContext()->VSSetConstantBuffers(0, 1, &transform_buffer);
	Game::instance->graphics.GetContext()->PSSetShaderResources(0, 1, &texture->pTextureRV);
	Game::instance->graphics.GetContext()->PSSetSamplers(0, 1, &texture->pSampler);

	model.Draw();
}

void RenderComponent::Initialize()
{
	// Init model
	if (!model.Initialize(modelPath))
	{
		std::cout << "failed to download model: " << modelPath << std::endl;
	}

	// Create transform buffer
	D3D11_BUFFER_DESC transformBufDesc = {};
	transformBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	transformBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transformBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	transformBufDesc.MiscFlags = 0;
	transformBufDesc.StructureByteStride = 0;
	transformBufDesc.ByteWidth = sizeof(ConstantData);
	Game::instance->graphics.GetDevice()->CreateBuffer(&transformBufDesc, nullptr, &transform_buffer);
}

void RenderComponent::Reload()
{
}

void RenderComponent::Update()
{
	constant_data.WorldViewProjection = XMMatrixTranspose(
		gameObject->transform.LocalToWorld()
		* Game::instance->mainCamera->ViewMatrix()
		* Game::instance->mainCamera->ProjectionMatrix()
	);

	D3D11_MAPPED_SUBRESOURCE res1 = {};
	Game::instance->graphics.GetContext()->Map(transform_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res1);
	auto dataPtr = (ConstantData*)(res1.pData);
	memcpy(dataPtr, &(constant_data), sizeof(ConstantData));
	Game::instance->graphics.GetContext()->Unmap(transform_buffer, 0);
}

void RenderComponent::Awake()
{
}

void RenderComponent::Start()
{
}

void RenderComponent::FixedUpdate()
{
}
