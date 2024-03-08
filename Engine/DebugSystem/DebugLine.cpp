#include "DebugLine.h"
#include "../GraphicsEngine/Shader.h"
#include "../GraphicsEngine/ShaderManager.h"
#include "../FileManager/BaseResources.h"
#include "../../App/Game.h"

using namespace DirectX;
namespace Debug 
{
	void DebugLine::Draw(const DirectX::XMFLOAT3& from, const DirectX::XMFLOAT3& to, const DirectX::XMFLOAT3& color)
	{
		/*XMFLOAT3 points[4] = { from, color, to, color };
		int indexes[2] = { 0,1 };

		const Shader* shader = ShaderManager::Get(BaseResource::lineDebugShader);
		auto context = Game::instance->graphics.GetContext();

		D3D11_BUFFER_DESC vertexBufDesc = {};
		vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufDesc.CPUAccessFlags = 0;
		vertexBufDesc.MiscFlags = 0;
		vertexBufDesc.StructureByteStride = 0;
		vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * 4;

		vertexData.pSysMem = points;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;


		D3D11_BUFFER_DESC indexBufDesc = {};
		indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufDesc.CPUAccessFlags = 0;
		indexBufDesc.MiscFlags = 0;
		indexBufDesc.StructureByteStride = 0;
		indexBufDesc.ByteWidth = sizeof(int) * 2;

		indexData.pSysMem = indexes;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;


		context->IASetInputLayout(shader->layout);
		context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		context->IASetIndexBuffer(mesh.ib, DXGI_FORMAT_R32_UINT, 0);
		context->IASetVertexBuffers(0, 1, &mesh.vb, strides, offsets);


		Game::instance->graphics.GetDevice()->CreateBuffer(&(mesh.vertexBufDesc), &(mesh.vertexData), &(mesh.vb));
		Game::instance->graphics.GetDevice()->CreateBuffer(&(mesh.indexBufDesc), &(mesh.indexData), &(mesh.ib));*/
	}
}