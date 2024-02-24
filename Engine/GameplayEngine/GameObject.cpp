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
	for (GameComponent* comp : components) {
		comp->Draw();
	}
}

void GameObject::Update(float deltaTime)
{
	for (GameComponent* comp : components) {
		comp->Update();
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
