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
	if (Game::instance->input->IsKeyDown(Keys::A))
	{
		gameObject->transform.Move(-gameObject->transform.Right() * Game::instance->time.GetDeltaTime() * moveSpeed);
	}
	if (Game::instance->input->IsKeyDown(Keys::D))
	{
		gameObject->transform.Move(gameObject->transform.Right() * Game::instance->time.GetDeltaTime() * moveSpeed);
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
	Vector2 offset = -args.Offset;
	gameObject->transform.RotateAroundAxis(Vector3::Up, offset.x * Game::instance->time.GetDeltaTime() * mouseSensevity);
	gameObject->transform.RotateAroundAxis(gameObject->transform.Right(), offset.y * Game::instance->time.GetDeltaTime() * mouseSensevity);
}
