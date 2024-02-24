#pragma once
class Physics;

#include "../GameplayEngine/GameComponents/Collider.h"
#include <vector>

class Physics
{
	friend class Collider;
	friend class BoxCollider;

public:
	~Physics();

	void Update();

private:
	void RemoveCollider(Collider* col);

private:
	std::vector<Collider*> collidersInGame;
};

