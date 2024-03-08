#pragma once

#include <vector>
#include <directxmath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <CommonStates.h>
#include <wrl.h>

namespace Debug
{
	class DebugGrid
	{
	public:
		void Init(int lines, int column, float cellSize);
		void ShotDown();
		void Draw();
	private:
		int lines_count;
		int column_count;
		float cell_size;
		DirectX::XMFLOAT4 color;

		std::vector<DirectX::XMFLOAT4> points;
		std::vector<int> indexes;

		std::unique_ptr<DirectX::CommonStates> m_states;
		std::unique_ptr<DirectX::BasicEffect> m_effect;
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	};
}

