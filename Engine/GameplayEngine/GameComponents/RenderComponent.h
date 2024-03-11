#pragma once
class RenderComponent;

#include "GameComponent.h"
#include "../../GraphicsEngine/GraphicsEngine.h"
#include "../../../App/Game.h"
#include "../../../Lib/Math/Math.h"

class RenderComponent : public GameComponent
{
public:
	struct ConstantData
	{
		SMath::Matrix WorldViewProjection;
	};
	static_assert((sizeof(ConstantData) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

public:
	RenderComponent() {};
	// Inherited via GameComponent
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Reload() override;
	void Update() override;
	void FixedUpdate() override;
	void Awake() override;
	void Start() override;
public:
	Mesh* mesh;
	Material* material;
private:
	ConstantData constant_data;
	ID3D11Buffer* transform_buffer = nullptr;
};

