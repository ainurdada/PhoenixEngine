#include "Box2D.h"

Mesh& Basic::Box2D::Create(float width, float height)
{
	std::vector<Vec4> points = {
		{-width / 2, -height / 2, 0.5f, 1}, Vec4(1.0f, 0.0f, 0.0f, 1.0f),
		{width / 2, height / 2, 0.5f, 1}, Vec4(0.0f, 1.0f, 0.0f, 1.0f),
		{width / 2, -height / 2, 0.5f, 1}, Vec4(1.0f, 1.0f, 1.0f, 1.0f),
		{-width / 2, height / 2, 0.5f, 1}, Vec4(0.0f, 0.0f, 1.0f, 1.0f),
	};
	std::vector<int> indexes = { 0,1,2, 1,0,3 };

	Mesh* pMesh = new Mesh(points, indexes);
	return *pMesh;
}
