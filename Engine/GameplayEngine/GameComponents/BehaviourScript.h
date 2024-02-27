#pragma once
#include "GameComponent.h"

class BehaviourScript : public GameComponent
{
public:
	virtual void Awake() override {};
	virtual void Start() override {};
	virtual void Update() override {};
	virtual void FixedUpdate() override {};
	virtual void DestroyResources() override {};
	virtual void Reload() override {};
private:
	virtual void Initialize() override;
	void Draw() override;
};

