#include "GameObject.h"

void GameObject::AddComponent(GameComponent& component)
{
	component.gameObject = this;
	components.push_back(&component);
}

void GameObject::Awake()
{
	for (GameComponent* comp : components) {
		comp->Awake();
	}
}

void GameObject::Start()
{
	for (GameComponent* comp : components) {
		comp->Start();
	}
}

void GameObject::Draw()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Draw();
	}
}

void GameObject::Update(float deltaTime)
{
	for (GameComponent* comp : components) {
		comp->Update();
	}
}
void GameObject::FixedUpdate()
{
	for (GameComponent* comp : components)
	{
		comp->FixedUpdate();
	}
}

void GameObject::DrawShadow(LightCamera* lightCamera)
{
	for (GameComponent* comp : components)
	{
		comp->DrawShadow(lightCamera);
	}
}

void GameObject::Release()
{
	for (GameComponent* comp : components) {
		comp->DestroyResources();
	}
}

void GameObject::Initialize()
{
	for (GameComponent* comp : components) {
		comp->Initialize();
	}
}

