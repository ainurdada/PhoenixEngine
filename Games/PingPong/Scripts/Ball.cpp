#include "Ball.h"

#include "Player.h"

void Ball::Awake()
{
	RenderComponent* rend = new RenderComponent;
	rend->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	rend->mesh = Basic::Box2D::Create(0.05f, 0.05f);
	gameObject->AddComponent(*rend);
}

void Ball::Update()
{
	gameObject->transform.position.x += velocity.x * Time::instance->GetDeltaTime();
	gameObject->transform.position.y += velocity.y * Time::instance->GetDeltaTime();

	if (gameObject->transform.position.y <= -0.975f) {
		velocity.y = -velocity.y;
	}
	if (gameObject->transform.position.y >= 0.975f) {
		velocity.y = -velocity.y;
	}
}

void Ball::DestroyResources()
{
}

void Ball::Reload()
{
}

void Ball::Start()
{
}
