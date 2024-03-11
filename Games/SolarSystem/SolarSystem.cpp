#include "SolarSystem.h"

#include "Scripts/CameraControl.h"
#include "Scripts/SolarSystemBehaviour.h"

void SolarSystem::OnCreated()
{
	CameraControl* cameraControl = new CameraControl;
	Game::instance->mainCamera->AddComponent(*cameraControl);

	GameObject* solarSystem = new GameObject;
	SolarSystemBehaviour* b = new SolarSystemBehaviour;
	solarSystem->AddComponent(*b);
	InstantiateGameObject(solarSystem);
}

void SolarSystem::OnDebugRender()
{
	Debug::DrawGrid(100, 100, 1, { 0.5f,0.5f,0.5f,0.5f });
}

void SolarSystem::OnClearResources()
{
}

void SolarSystem::OnUpdate()
{
}

void SolarSystem::OnFixedUpdate()
{
}
