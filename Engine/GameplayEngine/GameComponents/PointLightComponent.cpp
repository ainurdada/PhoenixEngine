#include "PointLightComponent.h"

#include "../../App/Game.h"

using namespace SMath;

void PointLightComponent::GenerateShadowMaps(GameObject* gameObjects[], int count)
{
	shadow_map[0].Generate(gameObjects, count);
}

void PointLightComponent::Awake()
{
}

void PointLightComponent::Start()
{
}

void PointLightComponent::Update()
{
	Game::instance->graphics.light.pointLights[index].color = color;
	Game::instance->graphics.light.pointLights[index].position = gameObject->transform.position();
	Game::instance->graphics.light.pointLights[index].intensity = intensity;
	Game::instance->graphics.light.pointLights[index].attenuation_a = attenuation_a;
	Game::instance->graphics.light.pointLights[index].attenuation_b = attenuation_b;
	Game::instance->graphics.light.pointLights[index].attenuation_c = attenuation_c;
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
	index = Game::instance->graphics.light.pointLights.size();
	Game::instance->graphics.light.pointLights.push_back({});
	Game::instance->pointLights.push_back(this);
	for (int i = 0; i < 6; i++)
	{
		cameras[i].transform.SetParent(&this->gameObject->transform);
		cameras[i].transform.localPosition({0,0,0});
	}
	cameras[0].SetRotation(-Vector3::Up, Vector3::Forward);
	shadow_map[0].Initialize(&cameras[0]);
}

void PointLightComponent::Reload()
{
}
