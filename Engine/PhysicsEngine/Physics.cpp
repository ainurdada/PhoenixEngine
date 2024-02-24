#include "Physics.h"

Physics::~Physics()
{
}

namespace er {
	static struct remove {
		Collider* key;
		remove(Collider* key) : key(key) {}

		bool operator()(Collider const* i) {
			return i == key;
		}
	};
}
void Physics::RemoveCollider(Collider* col)
{
	collidersInGame.erase(
		std::remove_if(
			collidersInGame.begin(),
			collidersInGame.end(),
			er::remove(col)),
		collidersInGame.end()
	);
}
