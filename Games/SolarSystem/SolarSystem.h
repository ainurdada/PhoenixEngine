#pragma once
#include "../../PhoenixEngine.h"

class SolarSystem : public Game
{
	// Inherited via Game
	void OnCreated() override;
	void OnDebugRender() override;
	void OnClearResources() override;
	void OnUpdate() override;
	void OnFixedUpdate() override;
};

