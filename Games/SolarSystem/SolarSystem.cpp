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

	debugGrid.Init(0, 0, 0);
}

void SolarSystem::OnDebugRender()
{
	debugGrid.Draw();
}

void SolarSystem::OnClearResources()
{
	debugGrid.ShotDown();
}

void SolarSystem::OnUpdate()
{
}

void SolarSystem::OnFixedUpdate()
{
}
