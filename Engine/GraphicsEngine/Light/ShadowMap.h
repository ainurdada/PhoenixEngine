#pragma once

#include <d3d11.h>

#include "LightCamera.h"
#include "../../GameplayEngine/GameObject.h"
#include "../Shader.h"

class ShadowMap
{
public:
	void Initialize(LightCamera* lightCamera);
	void Generate(GameObject gameObjects[], int count);
private:
	const Shader* shadowShader;
	LightCamera* light_camera;
	ID3D11DepthStencilView* depthDSV;
	ID3D11ShaderResourceView* depthSRV;
};

