#pragma once
class RenderComponent;

#include "GameComponent.h"
#include "../../GraphicsEngine/GraphicsEngine.h"
#include "../Game.h"
#include "../../Math/MathEngine.h"

class RenderComponent : public GameComponent
{
public:
	struct TransformData
	{
		Math::Vector4 position;
	};

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
	LPCWSTR shaderPath = L"";
private:
	TransformData transform_data;
	ID3D11Buffer* transform_buffer = nullptr;
};

