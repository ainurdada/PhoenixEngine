#pragma once

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "GameObject.h"

namespace {
	namespace erGameComponent {
		static struct remove {
			GameComponent* key;
			remove(GameComponent* key) : key(key) {}

			bool operator()(GameComponent const* i)
			{
				return i == key;
			}
		};
	}
}


template<typename T>
inline void GameObject::RemoveComponent()
{
	for (GameComponent* comp : components)
	{
		if (typeid(*comp) == typeid(T))
		{
			components.erase(
				std::remove_if(
					components.begin(),
					components.end(),
					erGameComponent::remove(comp)),
				components.end()
			);
			comp->DestroyResources();
			return;
		}
	}
}

template <typename T>
T* GameObject::GetComponent()
{
	for (GameComponent* comp : components) {
		if (typeid(*comp) == typeid(T)) {
			return (T*)comp;
		}
	}
	return nullptr;
}

#endif
