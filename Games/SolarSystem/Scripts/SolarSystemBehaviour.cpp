#include "SolarSystemBehaviour.h"
#include "Planet.h"

using namespace SMath;
GameObject* CreatePlanet(Vector3& pos)
{
	Vector3 size = { 1.f, 1.f, 1.f };
	GameObject* gameObj = new GameObject;
	RenderComponent* render = new RenderComponent;
	render->shaderPath = BaseResource::litShader;
	//render->mesh = Basic::Sphere::Create(1.f / 2.f, 20, 20);
	render->mesh = Basic::Box::Create(size, size);
	gameObj->AddComponent(*render);
	gameObj->transform.position(pos);
	return gameObj;
}
void SolarSystemBehaviour::Awake()
{
	cameraControl = Game::instance->mainCamera->GetComponent<CameraControl>();
	isPressed = false;

	focusIndex = -1;
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
			   -DirectX::XM_PIDIV4);
	//sun->transform.RotateAroundAxis(Vector3::Right, DirectX::XM_PIDIV2);
	Game::instance->InstantiateGameObject(sun);
	planets.push_back(sun);

	GameObject* planet1 = new GameObject;
	Planet* mercury = new Planet;
	pos = { 3, 2, 0 };
	planet1->AddComponent(*mercury);
	//planet1->transform.SetParent(&sun->transform);
	mercury->Init(pos,
				  &sun->transform,
				  up,
				  DirectX::XM_PIDIV4,
				  up,
				  DirectX::XM_PI);
	//planet1->transform.RotateAroundAxis(Vector3::Forward, DirectX::XM_PIDIV2);
	Game::instance->InstantiateGameObject(planet1);
	planets.push_back(planet1);

	GameObject* planet2 = new GameObject;
	Planet* venus = new Planet;
	pos = pos + Vector3::Up;
	Vector3 OrbitAxis = Vector3::Right;
	Vector3 SelfAxis = Vector3::Forward;
	planet2->AddComponent(*venus);
	//planet2->transform.SetParent(&mercury->gameObject->transform);
	planet2->transform.localScale({0.5f, 0.5f, 0.5f});
	venus->Init(pos,
				&mercury->gameObject->transform,
				OrbitAxis,
				  DirectX::XM_PIDIV4,
				SelfAxis,
				  DirectX::XM_PIDIV4);
	Game::instance->InstantiateGameObject(planet2);
	planets.push_back(planet2);

	GameObject* planet3 = new GameObject;
	Planet* earth = new Planet;
	pos = sun->transform.position() + Vector3::Up * 4 + Vector3::Right * 4;
	OrbitAxis = -Vector3::Right + Vector3::Up;
	OrbitAxis.Normalize();
	SelfAxis = Vector3::Forward;
	planet3->AddComponent(*earth);
	//planet2->transform.SetParent(&mercury->gameObject->transform);
	//planet3->transform.localScale({ 0.5f, 0.5f, 0.5f });
	earth->Init(pos,
				&sun->transform,
				OrbitAxis,
				DirectX::XM_PIDIV2,
				SelfAxis,
				DirectX::XM_PIDIV4);
	Game::instance->InstantiateGameObject(planet3);
	planets.push_back(planet3);


	/*Vector3 size = { .9f, .9f, .9f };
	float border = 1.1f;
	int countX = 20;
	int countY = 20;
	float startX = 0.5f - (float)countX * (size.x * border / 2.f);
	float startY = 0.5f - (float)countY * (size.z * border / 2.f);
	for (int i = 0; i < countX; i++)
	{
		for (int j = 0; j < countY; j++)
		{
			Vector3 pos = {
				startX + ((float)i) * size.x * border,
				-4,
				startY + ((float)j) * size.z * border
			};
			Game::instance->InstantiateGameObject(CreatePlanet(pos));
		}
	}*/
}

void SolarSystemBehaviour::Update()
{
	if (focusIndex != -1)
	{
		cameraControl->centerPoint = planets[focusIndex]->transform.position();
	}
	else
	{
		cameraControl->centerPoint = Vector3::One;
	}
	if (Game::instance->input->IsKeyDown(Keys::V))
	{
		if (!isPressed)
		{
			focusIndex++;
			if (focusIndex >= planets.size()) focusIndex = -1;
			if (focusIndex != -1)
			{
				cameraControl->distanceFromCenter =
					planets[focusIndex]->GetComponent<Planet>()->radius * planets[focusIndex]->transform.localScale().x /
					(sinf(Game::instance->mainCamera->fov() / 2 * DEG_TO_RAD));
			}
			isPressed = true;
		}
	}
	else
	{
		isPressed = false;
	}
}
