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

	SphereCollider* col = new SphereCollider;
	col->radius = 1;
	col->centerOffset = { 0,0.5f,0 };
	obj->AddComponent(*col);

	InstantiateGameObject(obj);
	obj->transform.localScale({ .05f,.05f,.05f });
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

	SphereCollider* col = new SphereCollider;
	col->radius = 1;
	col->centerOffset = { 0,0.5f,0 };
	obj->AddComponent(*col);

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
	obj->transform.position(position);

	SphereCollider* col = new SphereCollider;
	col->radius = 1;
	col->centerOffset = { 0,0.5f,0 };
	obj->AddComponent(*col);

	InstantiateGameObject(obj);
}

void KatamariGame::CreateDirLight(Vector3 direction, float intensity)
{
	GameObject* lightObj = new GameObject;
	DirectionalLightComponent* comp = new DirectionalLightComponent;
	comp->direction = direction;
	comp->intensity = intensity;
	comp->ambientKoeff = 0.1f;
	comp->specKoeff = 0.77f;
	comp->specPow = 89.6f;
	lightObj->AddComponent(*comp);
	InstantiateGameObject(lightObj);
}

void KatamariGame::CreatePointLight(Vector3 position, float intensity)
{
	GameObject* lightObj = new GameObject;
	PointLightComponent* comp = new PointLightComponent;
	comp->intensity = intensity;
	comp->color = { 1,1,1 };
	comp->attenuation_b = 0.1f;
	comp->attenuation_c = 0.01f;
	lightObj->transform.position(position);
	lightObj->transform.RotateAroundAxis(Vector3::Forward, 45 * DEG_TO_RAD);
	lightObj->AddComponent(*comp);
	InstantiateGameObject(lightObj);
}



void KatamariGame::OnCreated()
{
	CameraControl* cameraControl = new CameraControl;
	Game::instance->mainCamera->AddComponent(*cameraControl);

	GameObject* playerObj = new GameObject;
	Player* player = new Player;
	playerObj->AddComponent(*player);
	InstantiateGameObject(playerObj);
	cameraControl->player = &playerObj->transform;
	player->playerCamera = cameraControl;

	GameObject* floor = new GameObject;
	RenderComponent* floorRender = new RenderComponent;
	floorRender->modelPath = L"Models\\Room\\salt_tower_lower_room.glb";
	floorRender->shader = ShaderManager::Get(BaseResource::litShader);
	floor->AddComponent(*floorRender);
	floor->transform.scale({ 10,10,10 });
	floor->transform.position({ 0,-2.4f,0 });
	InstantiateGameObject(floor);

	

	CreateDirLight(Vector3::Down, 0);
	CreatePointLight({ 5,10,0 }, 5);

	int lines = 2;
	int columns = 2;
	float distance = 4;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Vector3 pos = Vector3::Zero + Vector3::Right * distance * i * 3 - Vector3::Forward * distance * j;
			CreateCrocodile(pos);
			pos = pos + Vector3::Right * distance;
			CreateDuriel(pos);
			pos = pos + Vector3::Right * distance;
			CreateScooter(pos);
		}
	}
}

void KatamariGame::OnUpdate()
{
}

void KatamariGame::OnFixedUpdate()
{
}

void KatamariGame::OnDebugRender()
{
	//Debug::DrawGrid(1000, 1000, 1, { 0.5f,0.5f,0.5f,1.0f });
}

void KatamariGame::OnClearResources()
{
}
