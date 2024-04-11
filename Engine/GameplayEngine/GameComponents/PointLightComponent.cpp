#include "PointLightComponent.h"

#include "../../App/Game.h"

using namespace SMath;
using namespace DirectX;

void PointLightComponent::GenerateShadowMaps(GameObject* gameObjects[], int count)
{
	shadow_map[0].Generate(gameObjects, count);
}

const std::vector<LightCamera> PointLightComponent::GetCameras() const
{
	return cameras;
}

const std::vector<ShadowMap> PointLightComponent::GetShadowMaps() const
{
	return shadow_map;
}

void PointLightComponent::Awake()
{
}

void PointLightComponent::Start()
{
}

void PointLightComponent::Update()
{
	for (LightCamera& camera : cameras) {
		camera.UpdateProjectionMatrix();
	}
}

void PointLightComponent::FixedUpdate()
{
}

void PointLightComponent::DestroyResources()
{
}

void PointLightComponent::Draw()
{
	DebugTool::Debug::DrawWiredSphere(this->gameObject->transform.position(), 0.1f, { 1,1,1,1 });
}

void PointLightComponent::Initialize()
{
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
