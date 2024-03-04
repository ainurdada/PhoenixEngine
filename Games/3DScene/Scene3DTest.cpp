#include "Scene3DTest.h"
#include "Scripts/TestBox.h"
#include "Scripts/CameraControl.h"

using namespace SMath;
GameObject* CreateBox(Vector3& pos)
{
	Vector3 size = { 1.f, 1.f, 1.f };
	TestBox* box = new TestBox;
	GameObject* gameObj = new GameObject;
	gameObj->AddComponent(*box);
	box->gameObject->transform.position(pos);
	return gameObj;
}
void Scene3DTest::Create()
{
	Game::Create();
	Vector3 size = { 1.f, 1.f, 1.f };
	float border = 1.f;
	int countX = 20;
	int countY = 10;
	float startX = 0.5f -(float)countX * (size.x * border / 2.f);
	float startY = 0.5f -(float)countY * (size.z * border / 2.f);
	for (int i = 0; i < countX; i++)
	{
		for (int j = 0; j < countY; j++)
		{
			Vector3 pos = {
				startX + ((float)i) * size.x * border,
				0,
				startY + ((float)j) * size.z * border
			};
			InstantiateGameObject(CreateBox(pos));
		}
	}
	Vector3 pos = { 0,0,0 };
	TestBox* box = new TestBox;
	GameObject* gameObj = new GameObject;
	gameObj->AddComponent(*box);
	//InstantiateGameObject(gameObj);

	CameraControl* camera = new CameraControl;
	Game::instance->mainCamera->AddComponent(*camera);
}


void Scene3DTest::Run()
{
	Game::Run();
}
