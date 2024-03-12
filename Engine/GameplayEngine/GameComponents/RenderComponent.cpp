#include "RenderComponent.h"
#include "../../GraphicsEngine/ShaderManager.h"
#include "../../../App/Game.h"

void RenderComponent::DestroyResources()
{
	model.Release();
}

#include "iostream"
using namespace DirectX;
void RenderComponent::Draw()
{
	// Set shader
	Game::instance->graphics.SetUpIA(*shader);
	Game::instance->graphics.SetShader(*shader);

	Game::instance->graphics.GetContext()->PSSetSamplers(0, 1, &Game::instance->graphics.pSampler);

	model.Draw(gameObject->transform.LocalToWorld());
}

void RenderComponent::Initialize()
{
	// Init model
	if (!model.Initialize(modelPath))
	{
		std::cout << "failed to download model: " << modelPath << std::endl;
	}
}

void RenderComponent::Reload()
{
}

void RenderComponent::Update()
{
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
