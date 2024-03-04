#include "SolarSystemBehaviour.h"
#include "Planet.h"

using namespace SMath;
GameObject* CreatePlanet(Vector3& pos)
{
	Vector3 size = { 1.f, 1.f, 1.f };
	GameObject* gameObj = new GameObject;
	RenderComponent* render = new RenderComponent;
	render->shaderPath = BaseResource::litShader;
	render->mesh = Basic::Sphere::Create(1.f / 2.f, 20, 20);
	gameObj->AddComponent(*render);
	gameObj->transform.position(pos);
	return gameObj;
}
void SolarSystemBehaviour::Awake()
{
	GameObject* sun = new GameObject;
	Planet* star = new Planet;
	Vector3 up = Vector3::Up;
	Vector3 pos = Vector3::Zero + Vector3::Up * 2;
	sun->AddComponent(*star);
	star->Init(pos,
				 nullptr,
				 up,
				 DirectX::XM_PI,
				 up,
				 DirectX::XM_PI);
	Game::instance->InstantiateGameObject(sun);

	GameObject* planet1 = new GameObject;
	Planet* mercury = new Planet;
	pos = { 3, 2, 0 };
	planet1->AddComponent(*mercury);
	mercury->Init(pos,
				  &sun->transform,
			   up,
			   DirectX::XM_PI,
			   up,
			   DirectX::XM_PI);
	Game::instance->InstantiateGameObject(planet1);

	Vector3 size = { 1.f, 1.f, 1.f };
	float border = 1.f;
	int countX = 20;
	int countY = 10;
	float startX = 0.5f - (float)countX * (size.x * border / 2.f);
	float startY = 0.5f - (float)countY * (size.z * border / 2.f);
	for (int i = 0; i < countX; i++)
	{
		for (int j = 0; j < countY; j++)
		{
			Vector3 pos = {
				startX + ((float)i) * size.x * border,
				0,
				startY + ((float)j) * size.z * border
			};
			Game::instance->InstantiateGameObject(CreatePlanet(pos));
		}
	}
}
