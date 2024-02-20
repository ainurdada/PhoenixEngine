#include "GameObject.h"

void GameObject::AddComponent(GameComponent& component)
{
	components.push_back(&component);
}

void GameObject::Draw()
{
	for (GameComponent* comp : components) {
		comp->Draw();
	}
}
