#include "PointLightComponent.h"

#include "../../App/Game.h"

using namespace SMath;
using namespace DirectX;

void PointLightComponent::GenerateShadowMaps(GameObject* gameObjects[], int count)
{
	for (int i = 0; i < 6; i++) {
		shadow_map[i].Generate(gameObjects, count);
	}
}

const std::vector<LightCamera> PointLightComponent::GetCameras() const
{
	return cameras;
}

const std::vector<ShadowMap> PointLightComponent::GetShadowMaps() const
{
	return shadow_map;
}

const std::vector<ID3D11ShaderResourceView*> PointLightComponent::GetShadowMapsResourceAdresses() const
{
	return resourceAdresses;
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
		cameras[i].transform.localPosition({ 0,0,0 });
	}
	cameras[0].SetRotation(-Vector3::Up, Vector3::Forward);
	cameras[1].SetRotation(Vector3::Up, -Vector3::Forward);
	cameras[2].SetRotation(Vector3::Forward, Vector3::Up);
	cameras[3].SetRotation(-Vector3::Forward, Vector3::Up);
	cameras[4].SetRotation(Vector3::Right, -Vector3::Up);
	cameras[5].SetRotation(-Vector3::Right, Vector3::Up);
	for (int i = 0; i < 6; i++) {
		shadow_map[i].Initialize(&cameras[i]);
		resourceAdresses[i] = shadow_map[i].GetShaderResource();
	}
}

void PointLightComponent::Reload()
{
}
