#include "GraphicsEngine/GraphicsEngine.h"
#include "App/GameComponents/RenderComponent.h"
#include "App/Game.h"
#include "App/GameObject.h"


Mesh& CreateMesh();


int main() {
	Game game;
	game.Create();

	GameObject gameObj;

	RenderComponent renderComponent;
	renderComponent.shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };
	renderComponent.shader.PSMacros = Shader_Macros;
	renderComponent.mesh = CreateMesh();

	gameObj.AddComponent(renderComponent);

	game.InstantiateGameObject(gameObj);

	gameObj.transform.position.x += 0.0f;

	game.Run();

	return 0;
}


Mesh& CreateMesh() {
	std::vector<Vec4> points = {
		Vec4(0.5f, 0.5f, 0.5f, 1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f),
		Vec4(-0.5f, -0.5f, 0.5f, 1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Vec4(0.5f, -0.5f, 0.5f, 1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f),
		Vec4(-0.5f, 0.5f, 0.5f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f),
	};
	std::vector<int> indeces = { 0,1,2, 1,0,3 };

	Mesh* pTriangle = new Mesh(points, indeces);
	return *pTriangle;
}
