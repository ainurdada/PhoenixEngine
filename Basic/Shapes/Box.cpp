#include "Box.h"
#include <vector>
#include <iostream>
using namespace GMath;
namespace Basic {
	Mesh& Box::Create(Vector3& extents, Vector3& color)
	{
		Vec4 start = { extents.x / -2.0f, extents.y / -2.0f, extents.z / -2.0f, 1.0f };
		std::vector<Vec4> points;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					Vec4 v = { i * extents.x, j * extents.y, k * extents.z, .0f };
					Vec4 c = { color.x * i, color.y * j, color.z * k, 1.0f };
					points.push_back(start + v);
					points.push_back(c);
				}
			}
		}
		for (int i = 0; i < points.size(); i++)
		{
			std::cout << points[i].x << " " << points[i].y << " " << points[i].z << std::endl;
		}
		std::vector<int> indexes = { 
			0,1,2, 1,3,2, // left
			0,5,1, 0,4,5, // down
			0,2,6, 0,6,4, // front
			4,6,5, 5,6,7, // right
			2,7,6, 3,7,2, // top
			1,7,3, 1,5,7, // back
		};

		Mesh* pMesh = new Mesh(points, indexes);
		return *pMesh;
	}
}