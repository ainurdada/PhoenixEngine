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
