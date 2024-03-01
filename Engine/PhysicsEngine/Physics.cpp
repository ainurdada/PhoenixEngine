#include "Physics.h"

#include "../GameplayEngine/GameComponents/BoxCollider.h"

Physics::~Physics()
{
}

void Physics::Update()
{
	for (Collider* col : collidersInGame) {
		BoxCollider* res;
		if (((BoxCollider*)col)->IsCollided(&res)) {
			std::cout << col->gameObject <<" collides " <<res->gameObject << "\n";
		}
	}
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