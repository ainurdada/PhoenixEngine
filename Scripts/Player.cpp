#include "Player.h"

#include "../App/Time.h"

void Player::DestroyResources()
{
}

void Player::Draw()
{
}

void Player::Initialize()
{
}

void Player::Reload()
{
}

#include "iostream"

void Player::Update()
{
	if (Game::instance->input->IsKeyDown(Keys::W)) {
		gameObject->transform.position.y += 0.5f * Time::instance->GetDeltaTime();
	}
	if (Game::instance->input->IsKeyDown(Keys::S)) {
		gameObject->transform.position.y -= 0.5f * Time::instance->GetDeltaTime();
	}
	if (Game::instance->input->IsKeyDown(Keys::A)) {
		gameObject->transform.position.x -= 0.5f * Time::instance->GetDeltaTime();
	}
	if (Game::instance->input->IsKeyDown(Keys::D)) {
		gameObject->transform.position.x += 0.5f * Time::instance->GetDeltaTime();
	}
}
