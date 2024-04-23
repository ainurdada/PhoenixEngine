#include "Physics.h"
#include "../GameplayEngine/GameComponents/SphereCollider.h"

#include "Simplex.h"

using namespace DirectX;
using namespace SMath;

Physics::~Physics()
{
}

#include <iostream>
void Physics::Update()
{
	for (int i = 0; i < collidersInGame.size(); i++)
	{
		if (!collidersInGame[i]->isEnable) continue;
		for (int j = i + 1; j < collidersInGame.size(); j++)
		{
			if (!collidersInGame[j]->isEnable) continue;
			if (CheckCollision(*collidersInGame[i], *collidersInGame[j]))
			{
				for (GameComponent* comp : collidersInGame[i]->gameObject->components)
				{
					comp->OnCollide(collidersInGame[j]);
				}
				for (GameComponent* comp : collidersInGame[j]->gameObject->components)
				{
					comp->OnCollide(collidersInGame[i]);
				}
			}
		}
	}
}

namespace er {
	static struct remove {
		Collider* key;
		remove(Collider* key) : key(key) {}

		bool operator()(Collider const* i)
		{
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


#include "../DebugSystem/DebugSystem.h"
bool Physics::CheckCollision(Collider& a, Collider& b)
{
	//return GJK(a, b);

	SphereCollider sa = (SphereCollider&)a;
	SphereCollider sb = (SphereCollider&)b;
	float dist = (a.position() - b.position()).Length();
	float radSum = sa.radius + sb.radius;
	if (dist > radSum)
	{
		return false;
	}
	else
	{
		return true;
	}
}

static bool Line(Simplex& points, Vector3& direction)
{
	Vector3 a = points[0];
	Vector3 b = points[1];

	Vector3 ab = b - a;
	Vector3 ao = -a;
	if (SameDirection(ab, ao))
	{
		direction = ab.Cross(ao).Cross(ab);
	}
	else
	{
		points = { a };
		direction = ao;
	}

	return false;
}

static bool Triangle(Simplex& points, Vector3& direction)
{
	Vector3 a = points[0];
	Vector3 b = points[1];
	Vector3 c = points[2];

	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 ao = -a;

	Vector3 abc = ab.Cross(ac);

	if (SameDirection(abc.Cross(ac), ao))
	{
		if (SameDirection(ac, ao))
		{
			points = { a,c };
			direction = ac.Cross(ao).Cross(ac);
		}
		else
		{
			return Line(points = { a,b }, direction);
		}
	}
	else
	{
		if (SameDirection(ab.Cross(abc), ao))
		{
			return Line(points = { a,b }, direction);
		}
		else
		{
			if (SameDirection(abc, ao))
			{
				direction = abc;
			}
			else
			{
				points = { a,c,b };
				direction = -abc;
			}
		}
	}
	return false;
}

static bool Tetrahedron(Simplex& points, Vector3& direction)
{
	Vector3 a = points[0];
	Vector3 b = points[1];
	Vector3 c = points[2];
	Vector3 d = points[3];

	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 ad = d - a;
	Vector3 ao = -a;

	Vector3 abc = ab.Cross(ac);
	Vector3 acd = ac.Cross(ad);
	Vector3 adb = ad.Cross(ab);

	if (SameDirection(abc, ao))
	{
		return Triangle(points = { a,b,c }, direction);
	}

	if (SameDirection(acd, ao))
	{
		return Triangle(points = { a,c,d }, direction);
	}

	if (SameDirection(adb, ao))
	{
		return Triangle(points = { a,d,b }, direction);
	}

	return true;
}

static bool NextSimplex(Simplex& points, Vector3& direction)
{
	switch (points.size())
	{
	case 2: return Line(points, direction);
	case 3: return Triangle(points, direction);
	case 4: return Tetrahedron(points, direction);
	}

	return false;
}

bool Physics::GJK(const Collider& a, const Collider& b)
{
	Vector3 support = Support(a, b, b.position() - a.position());

	Simplex points;
	points.push_front(support);

	Vector3 direction = -support;

	while (true)
	{
		support = Support(a, b, direction);
		if (support.Dot(direction) <= 0)
		{
			return false; // no collision
		}

		points.push_front(support);

		if (NextSimplex(points, direction))
		{
			return true;
		}
	}
}

SMath::Vector3 Physics::Support(const Collider& a, const Collider& b, Vector3 direction)
{
	return a.FindFurthestPoint(direction) - b.FindFurthestPoint(-direction);
}
