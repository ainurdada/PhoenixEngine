#include "Player.h"

void Player::Awake()
{
	LPCWSTR modelPath = L"Basic\\Shapes\\Models\\Sphere.glb";
	RenderComponent* rc = new RenderComponent;
	rc->shader = ShaderManager::Get(BaseResource::litShader);
	rc->modelPath = modelPath;
	gameObject->AddComponent(*rc);
	gameObject->transform.position(Vector3::Zero);
}

void Player::Update()
{
	if (playerCamera->rotateAroundCentre)
	{
		if (Game::instance->input->IsKeyDown(Keys::A))
		{
			gameObject->transform.Move(-playerCamera->gameObject->transform.Right() * Game::instance->time.GetDeltaTime() * moveSpeed);
		}
		if (Game::instance->input->IsKeyDown(Keys::D))
		{
			gameObject->transform.Move(playerCamera->gameObject->transform.Right() * Game::instance->time.GetDeltaTime() * moveSpeed);
		}
		Vector3 forward = gameObject->transform.Up().Cross(-playerCamera->gameObject->transform.Right());
		forward.Normalize();
		if (Game::instance->input->IsKeyDown(Keys::W))
		{
			gameObject->transform.Move(forward * Game::instance->time.GetDeltaTime() * moveSpeed);
		}
		if (Game::instance->input->IsKeyDown(Keys::S))
		{
			gameObject->transform.Move(-forward * Game::instance->time.GetDeltaTime() * moveSpeed);
		}
	}
}

void Player::Draw()
{
}
