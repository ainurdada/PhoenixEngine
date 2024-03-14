#pragma once

#include <directxmath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <CommonStates.h>
#include <wrl.h>


namespace DebugTool 
{
	class Debug
	{
	public:
		void Init();
		void ShotDown();

		static void DrawLine(DirectX::XMFLOAT3 from, DirectX::XMFLOAT3 to, DirectX::XMFLOAT4 color);
		static void DrawGrid(int lines, int column, float cellSize, DirectX::XMFLOAT4 color);
		static void DrawWiredSphere(const DirectX::XMFLOAT3& position, float radius, const DirectX::XMFLOAT4& color);

	private:
		static Debug* instance;

		std::unique_ptr<DirectX::CommonStates> m_states;
		std::unique_ptr<DirectX::BasicEffect> m_effect;
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	};
}

