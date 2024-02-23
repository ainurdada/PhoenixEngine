//#pragma once
#ifndef TRANSFORM_COMPONENT_DECLARATION
#define TRANSFORM_COMPONENT_DECLARATION
class TransformComponent;
#endif 


#include "GameComponent.h"
#include "../../Math/MathEngine.h"

#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
class TransformComponent : public GameComponent
{
public:
	TransformComponent() {};

	Math::Vector3 position = {0.0f, 0.0f, 0.0f};
	Math::Vector3 scale = {1.0f, 1.0f, 1.0f};

	// Inherited via GameComponent
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Reload() override;
	void Update() override;
};
#endif 

