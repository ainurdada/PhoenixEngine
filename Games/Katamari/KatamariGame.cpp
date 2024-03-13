#include "KatamariGame.h"

#include "Scripts/CameraControl.h"
#include "Scripts/Player.h"

void KatamariGame::CreateCrocodile(Vector3 position)
{
	LPCWSTR modelPath = L"Models\\Crocodile\\crocodile.glb";
	GameObject* obj = new GameObject;
	RenderComponent* rc = new RenderComponent;
	rc->shader = ShaderManager::Get(BaseResource::litShader);
	rc->modelPath = modelPath;
	obj->AddComponent(*rc);
	InstantiateGameObject(obj);
	obj->transform.localScale({ .1f,.1f,.1f });
	obj->transform.position(position);
}

void KatamariGame::CreateDuriel(Vector3 position)
{
	LPCWSTR modelPath = L"Models\\Duriel\\duriel.glb";
	GameObject* obj = new GameObject;
	RenderComponent* rc = new RenderComponent;
	rc->shader = ShaderManager::Get(BaseResource::litShader);
	rc->modelPath = modelPath;
	obj->AddComponent(*rc);
	InstantiateGameObject(obj);
	obj->transform.localScale({ .1f,.1f,.1f });
	obj->transform.position(position);
}

void KatamariGame::CreateScooter(Vector3 position)
{
	LPCWSTR modelPath = L"Models\\Scooter\\scooter.glb";
	GameObject* obj = new GameObject;
	RenderComponent* rc = new RenderComponent;
	rc->shader = ShaderManager::Get(BaseResource::litShader);
	rc->modelPath = modelPath;
	obj->AddComponent(*rc);
	InstantiateGameObject(obj);
	obj->transform.position(position);
}

void KatamariGame::OnCreated()
{
	CameraControl* cameraControl = new CameraControl;
	Game::instance->mainCamera->AddComponent(*cameraControl);

	//CreateCrocodile(Vector3::Zero);
	//CreateDuriel(Vector3::Zero);
	//CreateScooter(Vector3::Zero);

	GameObject* playerObj = new GameObject;
	Player* player = new Player;
	playerObj->AddComponent(*player);
	InstantiateGameObject(playerObj);
	cameraControl->player = &playerObj->transform;
	player->playerCamera = cameraControl;
}

void KatamariGame::OnUpdate()
{
}

void KatamariGame::OnFixedUpdate()
{
}

void KatamariGame::OnDebugRender()
{
	Debug::DrawGrid(1000, 1000, 1, { 0.5f,0.5f,0.5f,1.0f });
}

void KatamariGame::OnClearResources()
{
}
