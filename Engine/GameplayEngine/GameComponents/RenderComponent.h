#pragma once
class RenderComponent;

#include "GameComponent.h"
#include "../../GraphicsEngine/GraphicsEngine.h"
#include "../../../Lib/Math/Math.h"

class RenderComponent : public GameComponent
{
public:

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
	LPCWSTR modelPath;
	const Shader* shader;
private:
	Model model;
};

