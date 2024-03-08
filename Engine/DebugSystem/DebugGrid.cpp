#include "DebugGrid.h"
#include "../../App/Game.h"
#include <DirectXHelpers.h>
#include <SimpleMath.h>

using namespace DirectX;
using namespace SimpleMath;
namespace Debug
{
	void DebugGrid::Init(int lines, int column, float cellSize)
	{
		auto device = Game::instance->graphics.GetDevice().Get();
		m_states = std::make_unique<CommonStates>(device);

		m_effect = std::make_unique<BasicEffect>(device);
		m_effect->SetVertexColorEnabled(true);

		CreateInputLayoutFromEffect<VertexPositionColor>(device, m_effect.get(),
														 m_inputLayout.ReleaseAndGetAddressOf());

		auto context = Game::instance->graphics.GetContext();
		m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

		color = { 1,1,1,1 };
	}
	void DebugGrid::ShotDown()
	{
		m_states.reset();
		m_effect.reset();
		m_batch.reset();
		m_inputLayout.Reset();
	}
	void DebugGrid::Draw()
	{
		m_effect->SetWorld(XMMatrixIdentity());
		m_effect->SetView(Game::instance->mainCamera->ViewMatrix());
		m_effect->SetProjection(Game::instance->mainCamera->ProjectionMatrix());

		auto context = Game::instance->graphics.GetContext();


		m_effect->Apply(context);

		context->IASetInputLayout(m_inputLayout.Get());

		m_batch->Begin();

		Vector3 xaxis(2.f, 0.f, 0.f);
		Vector3 yaxis(0.f, 0.f, 2.f);
		Vector3 origin = Vector3::Zero;

		constexpr size_t divisions = 20;

		for (size_t i = 0; i <= divisions; ++i)
		{
			float fPercent = float(i) / float(divisions);
			fPercent = (fPercent * 2.0f) - 1.0f;

			Vector3 scale = xaxis * fPercent + origin;

			VertexPositionColor v1(scale - yaxis, color);
			VertexPositionColor v2(scale + yaxis, color);
			m_batch->DrawLine(v1, v2);
		}

		for (size_t i = 0; i <= divisions; i++)
		{
			float fPercent = float(i) / float(divisions);
			fPercent = (fPercent * 2.0f) - 1.0f;

			Vector3 scale = yaxis * fPercent + origin;

			VertexPositionColor v1(scale - xaxis, color);
			VertexPositionColor v2(scale + xaxis, color);
			m_batch->DrawLine(v1, v2);
		}

		m_batch->End();
	}
}