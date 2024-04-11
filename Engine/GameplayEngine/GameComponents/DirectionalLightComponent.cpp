#include "DirectionalLightComponent.h"

#include "../../App/Game.h"

#include <wrl.h>

void DirectionalLightComponent::Awake()
{
}

void DirectionalLightComponent::Start()
{
}

void DirectionalLightComponent::Update()
{
}

void DirectionalLightComponent::FixedUpdate()
{
}

void DirectionalLightComponent::DestroyResources()
{
}

void DirectionalLightComponent::Draw()
{
}

void DirectionalLightComponent::Initialize()
{
	Game::instance->dirLight = this;
}

void DirectionalLightComponent::Reload()
{
}
