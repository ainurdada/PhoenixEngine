#include "RenderComponent.h"

void RenderComponent::DestroyResources()
{
	shader.~Shader();
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

	// Create transform buffer
	D3D11_BUFFER_DESC transformBufDesc = {};
	transformBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	transformBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transformBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	transformBufDesc.MiscFlags = 0;
	transformBufDesc.StructureByteStride = 0;
	transformBufDesc.ByteWidth = sizeof(TransformData);
	Game::instance->graphics.GetDevice()->CreateBuffer(&transformBufDesc, nullptr, &transform_buffer);
	// Set transform buffer
	Game::instance->graphics.GetContext()->VSSetConstantBuffers(0, 1, &transform_buffer);
}

void RenderComponent::Reload()
{
}

void RenderComponent::Update()
{
	D3D11_MAPPED_SUBRESOURCE res = {};
	Game::instance->graphics.GetContext()->Map(transform_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res);
	auto dstPtr = reinterpret_cast<float*>(res.pData);
	auto srcPtr = &(gameObject->transform.position);
	memcpy(dstPtr, srcPtr, sizeof(TransformData));
	Game::instance->graphics.GetContext()->Unmap(transform_buffer, 0);
}
