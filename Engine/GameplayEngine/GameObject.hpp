#pragma once

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "GameObject.h"

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
