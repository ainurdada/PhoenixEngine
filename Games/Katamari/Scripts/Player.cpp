#include "Player.h"

void Player::Awake()
{
	LPCWSTR modelPath = L"Models\\Football/football.glb";
	RenderComponent* rc = new RenderComponent;
	rc->shader = ShaderManager::Get(BaseResource::litShader);
	rc->modelPath = modelPath;
	gameObject->AddComponent(*rc);
	gameObject->transform.position(Vector3::Zero + Vector3::Forward * 2);
	gameObject->transform.localScale({ .01f,.01f ,.01f });

	SphereCollider* col = new SphereCollider;
	col->radius = 0.6f;
	gameObject->AddComponent(*col);
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

void Player::OnCollide(Collider* other)
{
	std::cout << "Collide" << std::endl;
}
