#include "GameObject.h"

void GameObject::AddComponent(GameComponent* component)
{
	component->gameObject = this;
	components.push_back(component);
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
