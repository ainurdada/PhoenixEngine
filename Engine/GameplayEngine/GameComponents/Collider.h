#pragma once
class Collider;

#include "GameComponent.h"

class Collider : public GameComponent
{
public:

	bool IsCollisionEnter(GameObject* out);

private:
	// Inherited via GameComponent
	void Awake() override;
	void Start() override;
	void Update() override;
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Reload() override;

};

