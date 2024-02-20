#include "RenderComponent.h"

void RenderComponent::DestroyResources()
{
}

void RenderComponent::Draw()
{
	Game::instance->graphics.SetUpIA(shader.layout, mesh, shader);
	Game::instance->graphics.SetShader(shader);
}

void RenderComponent::Initialize()
{
	Game::instance->graphics.GetDevice()->CreateBuffer(&(mesh.vertexBufDesc), &(mesh.vertexData), &(mesh.vb));
	Game::instance->graphics.GetDevice()->CreateBuffer(&(mesh.indexBufDesc), &(mesh.indexData), &(mesh.ib));
	
	HRESULT res;
	shader.pathToShader = shaderPath;
	shader.device = Game::instance->graphics.GetDevice();
	res = this->shader.CompileVS(shader.VSMacros, shader.VSInclude);
	if (FAILED(res)) {
		Game::instance->window.ShowMessageBox(this->shader.pathToShader, L"Missing Shader File");
	}
	res = this->shader.CompilePS(shader.PSMacros, shader.PSInclude);
	res = this->shader.CreateInputLayout();
}

void RenderComponent::Reload()
{
}

void RenderComponent::Update()
{
}
