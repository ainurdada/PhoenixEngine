#include "TestBox.h"

using namespace SMath;
void TestBox::Awake()
{
	Vector3 ex = { .5f, .5f, .5f };
	Vector3 color = { 1.f, 1.f, 1.f };

	RenderComponent* r = new RenderComponent;
	r->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	r->shader.device = Game::instance->graphics.GetDevice();
	r->mesh = Basic::Box::Create(ex, color);
	gameObject->AddComponent(*r);
}

void TestBox::Start()
{
}

static float angleY = 0;
static float angleX = 0;

void TestBox::Update()
{
	Vector3 pos = gameObject->transform.localPosition();
	if (Game::instance->input->IsKeyDown(Keys::A))
	{
		gameObject->transform.localPosition(pos - Vector3::Right * Game::instance->time.GetDeltaTime());
	}
	if (Game::instance->input->IsKeyDown(Keys::D))
	{
		gameObject->transform.localPosition(pos + Vector3::Right * Game::instance->time.GetDeltaTime());
	}
	angleY = Game::instance->time.GetDeltaTime();
	gameObject->transform.RotateAroundAxis(Vector3::Up, angleY);
	/*if (Game::instance->input->IsKeyDown(Keys::E))
	{
	}
	if (Game::instance->input->IsKeyDown(Keys::Q))
	{
		angleY -= Game::instance->time.GetDeltaTime();
		Quaternion res;
		Quaternion::Create(GMath::Vector3::up, angleY, res);
		gameObject->transform.localRotation(res);
	}*/

	/*if (Game::instance->input->IsKeyDown(Keys::LeftShift))
	{
		angleX += Game::instance->time.GetDeltaTime();
		Quaternion res;
		Quaternion::Create(GMath::Vector3::right, angleX, res);
		gameObject->transform.localRotation(res);
	}
	if (Game::instance->input->IsKeyDown(Keys::LeftControl))
	{
		angleX -= Game::instance->time.GetDeltaTime();
		Quaternion res;
		Quaternion::Create(GMath::Vector3::right, angleX, res);
		gameObject->transform.localRotation(res);
	}*/
}
