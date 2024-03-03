#include "Scene3DTest.h"
#include "Scripts/TestBox.h"
#include "Scripts/CameraControl.h"

void Scene3DTest::Create()
{
	Game::Create();
	TestBox* box = new TestBox;
	GameObject* gameObj = new GameObject;
	gameObj->AddComponent(*box);
	InstantiateGameObject(gameObj);

	CameraControl* camera = new CameraControl;
	Game::instance->mainCamera->AddComponent(*camera);
}

void Scene3DTest::Run()
{
	Game::Run();
}
