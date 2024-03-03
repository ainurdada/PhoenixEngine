#include "Scene3DTest.h"
#include "Scripts/TestBox.h"

void Scene3DTest::Create()
{
	Game::Create();
	TestBox* box = new TestBox;
	GameObject* gameObj = new GameObject;
	gameObj->AddComponent(*box);
	InstantiateGameObject(gameObj);
}

void Scene3DTest::Run()
{
	Game::Run();
}
