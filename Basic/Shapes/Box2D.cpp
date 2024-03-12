#include "Box2D.h"
#include "../../Engine/GraphicsEngine/Vertex.h"
#include "../../App/Game.h"
#include "../../Basic/Constants/Colors.h"

Mesh& Basic::Box2D::Create(float width, float height)
{
	std::vector<Vertex> points = {
		{{-width / 2, -height / 2, 0.5f,1}, {1.0f, 0.0f, 0,0}},
		{{width / 2, height / 2, 0.5f,1}, {0.0f, 1.0f, 0,0}},
		{{width / 2, -height / 2, 0.5f,1}, {1.0f, 1.0f, 0,0}},
		{{-width / 2, height / 2, 0.5f,1}, {0.0f, 0.0f, 0,0}},
	};
	std::vector<int> indexes = { 0,1,2, 1,0,3 };

	std::vector<Texture> textures;
	textures.push_back(Texture(Game::instance->graphics.GetDevice().Get(), Basic::UnloadedTextureColor, aiTextureType_DIFFUSE));
	Mesh* pMesh = new Mesh(Game::instance->graphics.GetDevice().Get(), Game::instance->graphics.GetContext(), points, indexes, textures);
	return *pMesh;
}
