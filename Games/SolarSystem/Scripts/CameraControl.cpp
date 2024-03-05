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
	Vector2 offset = args.Position - prevMousePos;
	gameObject->transform.RotateAroundAxis(Vector3::Up, offset.x * Game::instance->time.GetDeltaTime() * mouseSensevity);
	gameObject->transform.RotateAroundLocalAxis(Vector3::Right, offset.y * Game::instance->time.GetDeltaTime() * mouseSensevity);
	prevMousePos = args.Position;
}
