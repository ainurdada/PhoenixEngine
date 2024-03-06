#include "CameraControl.h"
using namespace SMath;

void CameraControl::Awake()
{
	Game::instance->mainCamera->transform.position({ 0.f, 2.f, -10.0f });
}

void CameraControl::Start()
{
	Game::instance->input->MouseMove.AddRaw(this, &CameraControl::RotateCamera);
}

void CameraControl::Update()
{
	float angle = Game::instance->time.GetDeltaTime();
	Vector3 pos = gameObject->transform.localPosition();
	if (Game::instance->input->IsKeyDown(Keys::A))
	{
		gameObject->transform.localPosition(pos - gameObject->transform.Right() * Game::instance->time.GetDeltaTime() * moveSpeed);
	}
	if (Game::instance->input->IsKeyDown(Keys::D))
	{
		gameObject->transform.localPosition(pos + gameObject->transform.Right() * Game::instance->time.GetDeltaTime() * moveSpeed);
	}
	if (Game::instance->input->IsKeyDown(Keys::W))
	{
		gameObject->transform.Move(gameObject->transform.Forward() * Game::instance->time.GetDeltaTime() * moveSpeed);
	}
	if (Game::instance->input->IsKeyDown(Keys::S))
	{
		gameObject->transform.Move(-gameObject->transform.Forward() * Game::instance->time.GetDeltaTime() * moveSpeed);
	}

	if (Game::instance->input->IsKeyDown(Keys::Space))
	{
		gameObject->transform.Move(Vector3::Up * Game::instance->time.GetDeltaTime() * moveSpeed);
	}
	if (Game::instance->input->IsKeyDown(Keys::C))
	{
		gameObject->transform.Move(-Vector3::Up * Game::instance->time.GetDeltaTime() * moveSpeed);
	}

	if (Game::instance->input->IsKeyDown(Keys::NumPad1))
	{
		Game::instance->mainCamera->SetPerspective(true);
	}
	if (Game::instance->input->IsKeyDown(Keys::NumPad2))
	{
		Game::instance->mainCamera->SetPerspective(false);
	}
}

void CameraControl::FixedUpdate()
{
}

void CameraControl::DestroyResources()
{
}

void CameraControl::Reload()
{
}

void CameraControl::RotateCamera(const InputDevice::MouseMoveEventArgs& args)
{
	if (!Game::instance->input->IsKeyDown(Keys::LeftShift))
	{
		Vector2 offset = args.Offset;
		gameObject->transform.RotateAroundAxis(Vector3::Up, offset.x * Game::instance->time.GetDeltaTime() * mouseSensevity);
		gameObject->transform.RotateAroundLocalAxis(Vector3::Right, offset.y * Game::instance->time.GetDeltaTime() * mouseSensevity);
	}

	float deltaWheel = (float)args.WheelDelta * Game::instance->time.GetDeltaTime();
	Game::instance->mainCamera->zoom(Game::instance->mainCamera->zoom() + deltaWheel);
}
