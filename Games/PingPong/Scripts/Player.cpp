#include "Player.h"

void Player::DestroyResources()
{
}

void Player::Reload()
{
}

void Player::Update()
{
	SMath::Vector3 pos = gameObject->transform.position();
	if (!isEnemy) {
		if (Game::instance->input->IsKeyDown(Keys::W)) {
			pos.y += speed * Time::instance->GetDeltaTime();
		}
		if (Game::instance->input->IsKeyDown(Keys::S)) {
			pos.y -= speed * Time::instance->GetDeltaTime();
		}
	}
	else
	{
		if (Game::instance->input->IsKeyDown(Keys::Up)) {
			pos.y += speed * Time::instance->GetDeltaTime();
		}
		if (Game::instance->input->IsKeyDown(Keys::Down)) {
			pos.y -= speed * Time::instance->GetDeltaTime();
		}
	}
	pos.y = pos.y > (1 - size.y / 2) ? (1 - size.y / 2) : pos.y;
	pos.y = pos.y < (-1 + size.y / 2) ? (-1 + size.y / 2) : pos.y;
	gameObject->transform.position(pos);
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
	gameObject->transform.position(startPosition);
}
