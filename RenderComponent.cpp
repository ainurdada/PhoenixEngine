#include "RenderComponent.h"

void RenderComponent::DestroyResources()
{
}

void RenderComponent::Draw()
{
	Game::instance->graphics.SetUpIA(shader.layout, mesh, shader);
	Game::instance->graphics.SetShader(shader);
	Game::instance->graphics.GetContext()->DrawIndexed(mesh.indexes.size(), 0, 0);
}

void RenderComponent::Initialize()
{
	HRESULT res;
	shader.pathToShader = shaderPath;
	shader.device = Game::instance->graphics.GetDevice();
	res = this->shader.CompileVS(shader.VSMacros, shader.VSInclude);
	if (FAILED(res)) {
		Game::instance->window.ShowMessageBox(this->shader.pathToShader, L"Missing Shader File");
	}
	res = this->shader.CompilePS(shader.PSMacros, shader.PSInclude);
	res = this->shader.CreateInputLayout();

	Game::instance->graphics.GetDevice()->CreateBuffer(&(mesh.vertexBufDesc), &(mesh.vertexData), &(mesh.vb));
	Game::instance->graphics.GetDevice()->CreateBuffer(&(mesh.indexBufDesc), &(mesh.indexData), &(mesh.ib));
}

void RenderComponent::Reload()
{
}

void RenderComponent::Update()
{
}
