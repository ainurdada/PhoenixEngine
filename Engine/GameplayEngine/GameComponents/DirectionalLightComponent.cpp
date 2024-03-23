#include "DirectionalLightComponent.h"

#include "../../App/Game.h"

void DirectionalLightComponent::Awake()
{
}

void DirectionalLightComponent::Start()
{
}

void DirectionalLightComponent::Update()
{
	Game::instance->graphics.light.dirLight.direction = direction;
	Game::instance->graphics.light.dirLight.intensity = intensity;
	Game::instance->graphics.light.dirLight.KaSpecPowKsX.x = ambientKoeff;
	Game::instance->graphics.light.dirLight.KaSpecPowKsX.y = specPow;
	Game::instance->graphics.light.dirLight.KaSpecPowKsX.z = specKoeff;
	Game::instance->graphics.light.dirLight.KaSpecPowKsX.w = 0;
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
}

void DirectionalLightComponent::Reload()
{
}
