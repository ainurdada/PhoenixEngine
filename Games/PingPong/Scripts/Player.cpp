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
			gameObject->transform.position.y += speed * Time::instance->GetDeltaTime();
		}
		if (Game::instance->input->IsKeyDown(Keys::S)) {
			gameObject->transform.position.y -= speed * Time::instance->GetDeltaTime();
		}
	}
	else
	{
		if (Game::instance->input->IsKeyDown(Keys::Up)) {
			gameObject->transform.position.y += speed * Time::instance->GetDeltaTime();
		}
		if (Game::instance->input->IsKeyDown(Keys::Down)) {
			gameObject->transform.position.y -= speed * Time::instance->GetDeltaTime();
		}
	}
	gameObject->transform.position.y = gameObject->transform.position.y > (1 - size.y / 2) ? (1 - size.y / 2) : gameObject->transform.position.y;
	gameObject->transform.position.y = gameObject->transform.position.y < (-1 + size.y / 2) ? (-1 + size.y / 2) : gameObject->transform.position.y;
}

void Player::Awake()
{
	RenderComponent* renderComponent = new RenderComponent();
	renderComponent->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	renderComponent->mesh = Basic::Box2D::Create(size.x, size.y);
	gameObject->AddComponent(*renderComponent);
	BoxCollider* collider = new BoxCollider;
	collider->size = { size.x, size.y };
	gameObject->AddComponent(*collider);
}

void Player::Start()
{
	gameObject->transform.position = startPosition;
}
