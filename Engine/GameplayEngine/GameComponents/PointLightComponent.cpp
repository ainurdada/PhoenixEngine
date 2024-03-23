#include "PointLightComponent.h"

#include "../../App/Game.h"

void PointLightComponent::Awake()
{
	index = Game::instance->graphics.light.pointLights.size();
	Game::instance->graphics.light.pointLights.push_back({});
}

void PointLightComponent::Start()
{
}

void PointLightComponent::Update()
{
	Game::instance->graphics.light.pointLights[index].position = gameObject->transform.position();
	Game::instance->graphics.light.pointLights[index].intensity = intensity;
}

void PointLightComponent::FixedUpdate()
{
}

void PointLightComponent::DestroyResources()
{
}

void PointLightComponent::Draw()
{
}

void PointLightComponent::Initialize()
{
}

void PointLightComponent::Reload()
{
}
