#pragma once
class Collider;

#include "GameComponent.h"

class Collider : public GameComponent
{
protected:
	virtual void DestroyResources() override;
	virtual void Initialize() override;
private:
	// Inherited via GameComponent
	void Awake() override;
	void Start() override;
	void Draw() override;
	void Reload() override;

};

