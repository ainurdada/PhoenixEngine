#include "Box.h"
#include "../../Engine/GraphicsEngine/Vertex.h"
#include <vector>
#include <iostream>
#include "../../App/Game.h"
#include "../../Basic/Constants/Colors.h"
using namespace SMath;
namespace Basic {
	Mesh& Box::Create(Vector3& extents, Vector3& color)
	{
		Vec4 start = { extents.x / -2.0f, extents.y / -2.0f, extents.z / -2.0f, 1.0f };
		std::vector<Vertex> points;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					Vector3 v = { i * extents.x, j * extents.y, k * extents.z };
					Vector3 c = { color.x * i, color.y * j, color.z * k };
					Vertex vert = { v,c };
					points.push_back(vert);
				}
			}
		}
		std::vector<int> indexes = {
			0,1,2, 1,3,2, // left
			0,5,1, 0,4,5, // down
			0,2,6, 0,6,4, // front
			4,6,5, 5,6,7, // right
			2,7,6, 3,7,2, // top
			1,7,3, 1,5,7, // back
		};

		std::vector<Texture> textures;
		textures.push_back(Texture(Game::instance->graphics.GetDevice().Get(), Basic::UnloadedTextureColor, aiTextureType_DIFFUSE));
		Mesh* pMesh = new Mesh(
			Game::instance->graphics.GetDevice().Get(), 
			Game::instance->graphics.GetContext(), 
			points, 
			indexes, 
			textures, 
			DirectX::XMMatrixIdentity());
		return *pMesh;
	}
}