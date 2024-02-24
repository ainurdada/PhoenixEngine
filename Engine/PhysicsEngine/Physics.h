#pragma once
class Physics;

#include "../GameplayEngine/GameComponents/Collider.h"
#include <vector>

class Physics
{
	friend class Collider;

public:
	~Physics();

private:
	void RemoveCollider(Collider* col);

private:
	std::vector<Collider*> collidersInGame;
};

