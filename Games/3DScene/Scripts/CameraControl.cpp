#include "CameraControl.h"
using namespace SMath;

void CameraControl::Awake()
{
	Game::instance->mainCamera->transform.position({ 0.f, 0.f, -5.0f });
}

void CameraControl::Start()
{
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

	if (Game::instance->input->IsKeyDown(Keys::E))
	{
		gameObject->transform.RotateAroundAxis(Vector3::Up, Game::instance->time.GetDeltaTime() * moveSpeed);
	}
	if (Game::instance->input->IsKeyDown(Keys::Q))
	{
		gameObject->transform.RotateAroundAxis(Vector3::Up, -Game::instance->time.GetDeltaTime() * moveSpeed);
	}
	if (Game::instance->input->IsKeyDown(Keys::F))
	{
		gameObject->transform.RotateAroundAxis(gameObject->transform.Right(), Game::instance->time.GetDeltaTime() * moveSpeed);
	}
	if (Game::instance->input->IsKeyDown(Keys::R))
	{
		gameObject->transform.RotateAroundAxis(gameObject->transform.Right(), -Game::instance->time.GetDeltaTime() * moveSpeed);
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
