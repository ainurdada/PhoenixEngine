#include "RenderComponent.h"
#include "../../GraphicsEngine/ShaderManager.h"

void RenderComponent::DestroyResources()
{
	transform_buffer->Release();
}

#include "iostream"
using namespace DirectX;
void RenderComponent::Draw()
{
	matrix_data.world = XMMatrixTranspose(gameObject->transform.LocalToWorld());
	matrix_data.view = XMMatrixTranspose(Game::instance->mainCamera->ViewMatrix());
	matrix_data.projection = XMMatrixTranspose(Game::instance->mainCamera->ProjectionMatrix());

	D3D11_MAPPED_SUBRESOURCE res1 = {};
	Game::instance->graphics.GetContext()->Map(transform_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res1);
	auto dataPtr = (MatrixData*)(res1.pData);
	memcpy(dataPtr, &(matrix_data), sizeof(MatrixData));
	Game::instance->graphics.GetContext()->Unmap(transform_buffer, 0);

	Game::instance->graphics.SetUpIA(shader->layout, mesh, *shader);

	// Set shader
	Game::instance->graphics.GetContext()->VSSetConstantBuffers(0, 1, &transform_buffer);
	Game::instance->graphics.SetShader(*shader);

	Game::instance->graphics.GetContext()->DrawIndexed(mesh.indexes.size(), 0, 0);
}

void RenderComponent::Initialize()
{
	HRESULT res;
	shader = ShaderManager::Get(shaderPath);

	// Create transform buffer
	D3D11_BUFFER_DESC transformBufDesc = {};
	transformBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	transformBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transformBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	transformBufDesc.MiscFlags = 0;
	transformBufDesc.StructureByteStride = 0;
	transformBufDesc.ByteWidth = sizeof(MatrixData);
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

void RenderComponent::Awake()
{
}

void RenderComponent::Start()
{
}

void RenderComponent::FixedUpdate()
{
}
