#include "Sphere.h"
#include "../../Engine/GraphicsEngine/Vertex.h"
#include "cmath"
#include "../../App/Game.h"
#include "../../Basic/Constants/Colors.h"
using namespace DirectX;
using namespace SMath;
namespace Basic
{
	Mesh& Sphere::Create(float radius, int sliceCount, int stackCount)
	{
		float phiStep = XM_PI / stackCount;
		float thetaStep = 2.0f * XM_PI / sliceCount;
		std::vector<Vertex> points;
		std::vector<int> indexes;

		Vector4 pos = { 0, radius,0,1 };
		Vector4 tex = { 0,0,0,0 };
		Vertex vert = { pos, tex };
		points.push_back(vert);
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
				pos = { p.x,p.y,p.z,1 };
				tex = { theta / (XM_PI * 2), phi / XM_PI };
				vert = { pos, tex };
				points.push_back(vert);
			}
		}
		pos = { 0, -radius, 0 };
		tex = { 0,1 };
		vert = { pos, tex };
		points.push_back(vert);

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