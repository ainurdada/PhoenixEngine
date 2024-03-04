#include "Sphere.h"
#include "cmath"
using namespace DirectX;
using namespace SMath;
namespace Basic
{
	Mesh& Sphere::Create(float radius)
	{
		int sliceCount = 10;
		int stackCount = 10;

		

		float phiStep = XM_PI / stackCount;
		float thetaStep = 2.0f * XM_PI / sliceCount;
		std::vector<Vec4> points;
		std::vector<int> indexes;

		points.push_back({ 0, radius,0, 1 });
		points.push_back({ 0, 0, 0, 1 });
		for (int i = 1; i <= stackCount - 1; i++)
		{
			float phi = i * phiStep;
			for (int j = 0; j <= sliceCount; j++)
			{
				float theta = j * thetaStep;
				Vector3 p = Vector3(
					(radius * sinf(phi) * cosf(theta)),
					(radius * cosf(phi)),
					(radius * sinf(phi) * sinf(theta))
				);
				points.push_back({ p.x,p.y,p.z,1 });
				points.push_back({ 1,1,1,1 });
			}
		}
		points.push_back({ 0, -radius, 0, 1 });
		points.push_back({ 0, 0, 0, 1 });

		for (int i = 1; i <= sliceCount; i++)
		{
			indexes.push_back(0);
			indexes.push_back(i + 1);
			indexes.push_back(i);
		}
		int baseIndex = 1;
		int ringVertexCount = sliceCount + 1;
		for (int i = 0; i < stackCount - 2; i++)
		{
			for (int j = 0; j < sliceCount; j++)
			{
				indexes.push_back(baseIndex + i * ringVertexCount + j);
				indexes.push_back(baseIndex + i * ringVertexCount + j + 1);
				indexes.push_back(baseIndex + (i + 1) * ringVertexCount + j);

				indexes.push_back(baseIndex + (i + 1) * ringVertexCount + j);
				indexes.push_back(baseIndex + i * ringVertexCount + j + 1);
				indexes.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
			}
		}
		int southPoleIndex = points.size() - 1;
		baseIndex = southPoleIndex - ringVertexCount;
		for (int i = 0; i < sliceCount; i++)
		{
			indexes.push_back(southPoleIndex);
			indexes.push_back(baseIndex + i);
			indexes.push_back(baseIndex + i + 1);
		}

		Mesh* mesh = new Mesh(points, indexes);
		return *mesh;
	}
}