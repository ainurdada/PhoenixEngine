#include "SolarSystemBehaviour.h"

using namespace SMath;
GameObject* CreatePlanet(Vector3& pos)
{
	Vector3 size = { 1.f, 1.f, 1.f };
	GameObject* gameObj = new GameObject;
	RenderComponent* render = new RenderComponent;
	render->shaderPath = BaseResource::litShader;
	render->mesh = Basic::Box::Create(size, size);
	gameObj->AddComponent(*render);
	gameObj->transform.position(pos);
	return gameObj;
}
void SolarSystemBehaviour::Awake()
{
	/*GameObject* sun = new GameObject;
	RenderComponent* sunRender = new RenderComponent;
	sunRender->shader.pathToShader = BaseResource::litShader;
	sunRender->shader.device = Game::instance->graphics.GetDevice();
	sunRender->mesh = Basic::Sphere::Create(1.f);
	sun->AddComponent(*sunRender);
	Game::instance->InstantiateGameObject(sun);*/

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
