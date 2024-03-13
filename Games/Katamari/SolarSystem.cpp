#include "SolarSystem.h"

#include "Scripts/CameraControl.h"

void SolarSystem::OnCreated()
{

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
