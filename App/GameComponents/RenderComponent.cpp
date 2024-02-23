#include "RenderComponent.h"

void RenderComponent::DestroyResources()
{
	shader.~Shader();
}

#include "iostream"
void RenderComponent::Draw()
{
	transform_data.position.x = gameObject->transform.position.x;
	transform_data.position.y = gameObject->transform.position.y;
	transform_data.position.z = gameObject->transform.position.z;
	D3D11_MAPPED_SUBRESOURCE res1 = {};
	Game::instance->graphics.GetContext()->Map(transform_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res1);
	auto dataPtr = (TransformData*)(res1.pData);
	memcpy(dataPtr, &(transform_data), sizeof(TransformData));
	Game::instance->graphics.GetContext()->Unmap(transform_buffer, 0);

	Game::instance->graphics.SetUpIA(shader.layout, mesh, shader);

	// Set shader
	Game::instance->graphics.GetContext()->VSSetConstantBuffers(0, 1, &transform_buffer);
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

	// Create transform buffer
	D3D11_BUFFER_DESC transformBufDesc = {};
	transformBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	transformBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transformBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	transformBufDesc.MiscFlags = 0;
	transformBufDesc.StructureByteStride = 0;
	transformBufDesc.ByteWidth = sizeof(TransformData);
	Game::instance->graphics.GetDevice()->CreateBuffer(&transformBufDesc, nullptr, &transform_buffer);

	Game::instance->graphics.GetDevice()->CreateBuffer(&(mesh.vertexBufDesc), &(mesh.vertexData), &(mesh.vb));
	Game::instance->graphics.GetDevice()->CreateBuffer(&(mesh.indexBufDesc), &(mesh.indexData), &(mesh.ib));
}

void RenderComponent::Reload()
{
}

void RenderComponent::Update()
{
}
