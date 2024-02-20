#pragma once
class RenderComponent;

#include "GameComponent.h"
#include "GraphicsEngine.h"
#include "Mesh.h"
#include "Game.h"

class RenderComponent : public GameComponent
{
public:
	RenderComponent() {};
	// Inherited via GameComponent
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Reload() override;
	void Update() override;
public:
	Mesh mesh;
	Shader shader;
	LPCWSTR shaderPath = L"emty";

private:
};

