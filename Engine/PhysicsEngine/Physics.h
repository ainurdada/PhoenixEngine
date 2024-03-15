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
	bool CheckCollision(Collider& a, Collider& b);
	bool GJK(const Collider& a, const Collider& b);
	SMath::Vector3 Support(const Collider& a, const Collider& b, SMath::Vector3 direction);

private:
	std::vector<Collider*> collidersInGame;
};

