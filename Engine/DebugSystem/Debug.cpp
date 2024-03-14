#include "Debug.h"
#include "../../App/Game.h"
#include <DirectXHelpers.h>
#include <GeometricPrimitive.h>

using namespace DirectX;
using namespace SimpleMath;

namespace DebugTool
{
	Debug* Debug::instance;

	void Debug::Init()
	{
		instance = this;
		auto device = Game::instance->graphics.GetDevice().Get();
		m_states = std::make_unique<CommonStates>(device);

		m_effect = std::make_unique<BasicEffect>(device);
		m_effect->SetVertexColorEnabled(true);

		CreateInputLayoutFromEffect<VertexPositionColor>(device, m_effect.get(),
														 m_inputLayout.ReleaseAndGetAddressOf());

		auto context = Game::instance->graphics.GetContext();
		m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
	}

	void Debug::ShotDown()
	{
		m_states.reset();
		m_effect.reset();
		m_batch.reset();
		m_inputLayout.Reset();
	}

	void Debug::DrawLine(DirectX::XMFLOAT3 from, DirectX::XMFLOAT3 to, DirectX::XMFLOAT4 color)
	{
		instance->m_effect->SetWorld(XMMatrixIdentity());
		instance->m_effect->SetView(Game::instance->mainCamera->ViewMatrix());
		instance->m_effect->SetProjection(Game::instance->mainCamera->ProjectionMatrix());

		auto context = Game::instance->graphics.GetContext();


		instance->m_effect->Apply(context);

		context->IASetInputLayout(instance->m_inputLayout.Get());

		instance->m_batch->Begin();

		VertexPositionColor v1(from, color);
		VertexPositionColor v2(to, color);
		instance->m_batch->DrawLine(v1, v2);

		instance->m_batch->End();
	}
	void Debug::DrawGrid(int lines, int column, float cellSize, DirectX::XMFLOAT4 color)
	{
		Vector3 xaxis = Vector3::Right * column * cellSize / 2.0f;
		Vector3 yaxis = Vector3::Forward * lines * cellSize / 2.0f;
		Vector3 origin = Vector3::Zero;

		constexpr size_t divisions = 20;

		for (size_t i = 0; i <= column; ++i)
		{
			float fPercent = float(i) / float(column);
			fPercent = (fPercent * 2.0f) - 1.0f;

			Vector3 scale = xaxis * fPercent + origin;

			Debug::DrawLine(scale - yaxis, scale + yaxis, color);
		}

		for (size_t i = 0; i <= lines; i++)
		{
			float fPercent = float(i) / float(lines);
			fPercent = (fPercent * 2.0f) - 1.0f;

			Vector3 scale = yaxis * fPercent + origin;

			Debug::DrawLine(scale - xaxis, scale + xaxis, color);
		}
	}

	using namespace DirectX;
	void Debug::DrawWiredSphere(const DirectX::XMFLOAT3& position, float radius, const DirectX::XMFLOAT4& color)
	{
		std::unique_ptr<GeometricPrimitive> sphere;
		sphere = GeometricPrimitive::CreateSphere(Game::instance->graphics.GetContext());
		XMMATRIX world = XMMatrixTranslation(position.x, position.y, position.z);
		sphere->Draw(
			world,
			Game::instance->mainCamera->ViewMatrix(),
			Game::instance->mainCamera->ProjectionMatrix(),
			{ color.x, color.y, color.z, color.w },
			nullptr,
			true
		);
	}
}