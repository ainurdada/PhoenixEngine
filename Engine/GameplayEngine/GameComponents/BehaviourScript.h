#pragma once
#include "GameComponent.h"

class BehaviourScript : public GameComponent
{
public:
	virtual void Awake() override = 0;
	virtual void Start() override = 0;
	virtual void Update() override = 0;
	virtual void DestroyResources() override = 0;
	virtual void Reload() override = 0;
private:
	virtual void Initialize() override;
	void Draw() override;
};

