#include "Player.h"

void Player::DestroyResources()
{
}

void Player::Reload()
{
}

void Player::Update()
{
	if (!isEnemy) {
		if (Game::instance->input->IsKeyDown(Keys::W)) {
			gameObject->transform.position.y += 0.5f * Time::instance->GetDeltaTime();
		}
		if (Game::instance->input->IsKeyDown(Keys::S)) {
			gameObject->transform.position.y -= 0.5f * Time::instance->GetDeltaTime();
		}
	}
	else
	{
		if (Game::instance->input->IsKeyDown(Keys::Up)) {
			gameObject->transform.position.y += 0.5f * Time::instance->GetDeltaTime();
		}
		if (Game::instance->input->IsKeyDown(Keys::Down)) {
			gameObject->transform.position.y -= 0.5f * Time::instance->GetDeltaTime();
		}
	}
}

void Player::Awake()
{
	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	renderComponent->mesh = Basic::Box2D::Create(0.05f, 0.2f);
	gameObject->AddComponent(*renderComponent);
	BoxCollider* collider = new BoxCollider;
	collider->size = { 0.05, 0.2f };
	gameObject->AddComponent(*collider);
}

void Player::Start()
{
	gameObject->transform.position = startPosition;
}
