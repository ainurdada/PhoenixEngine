#pragma once

#include "../../PhoenixEngine.h"

class KatamariGame : public Game
{
	void CreateCrocodile(Vector3 position);
	void CreateDuriel(Vector3 position);
	void CreateScooter(Vector3 position);

	// Inherited via Game
	void OnCreated() override;
	void OnUpdate() override;
	void OnFixedUpdate() override;
	void OnDebugRender() override;
	void OnClearResources() override;
};

