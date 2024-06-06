#include "Player.h"

void Player::Awake()
{
	LPCWSTR modelPath = L"Models\\Football/football.glb";
	RenderComponent* rc = new RenderComponent;
	rc->shader = ShaderManager::Get(BaseResource::litShader);
	rc->modelPath = modelPath;
	gameObject->AddComponent(*rc);
	gameObject->transform.position(Vector3::Forward * 2 + Vector3::Up * 0.6f);
	gameObject->transform.localScale({ .01f,.01f ,.01f });

	SphereCollider* col = new SphereCollider;
	col->radius = 0.6f;
	gameObject->AddComponent(*col);
}

void Player::Update()
{
	Vector3 oldPos = gameObject->transform.position();
	for (Collider* col : m_collidersToDelete)
	{
		//this->gameObject->GetComponent<SphereCollider>()->radius += ((SphereCollider*)col)->radius*2;
		col->gameObject->RemoveComponent<SphereCollider>();
	}
	m_collidersToDelete.clear();

	if (playerCamera->rotateAroundCentre)
	{
		if (Game::instance->input->IsKeyDown(Keys::A))
		{
			gameObject->transform.Move(-playerCamera->gameObject->transform.Right() * Game::instance->time.GetDeltaTime() * moveSpeed);
		}
		if (Game::instance->input->IsKeyDown(Keys::D))
		{
			gameObject->transform.Move(playerCamera->gameObject->transform.Right() * Game::instance->time.GetDeltaTime() * moveSpeed);
		}
		Vector3 forward = Vector3::Up.Cross(-playerCamera->gameObject->transform.Right());
		forward.Normalize();
		if (Game::instance->input->IsKeyDown(Keys::W))
		{
			gameObject->transform.Move(forward * Game::instance->time.GetDeltaTime() * moveSpeed);
		}
		if (Game::instance->input->IsKeyDown(Keys::S))
		{
			gameObject->transform.Move(-forward * Game::instance->time.GetDeltaTime() * moveSpeed);
		}

		Vector3 moveDirection = gameObject->transform.position() - oldPos;
		if (moveDirection != DirectX::XMVectorZero())
		{
			Vector3 rotationAxis = Vector3::Up.Cross(moveDirection);
			gameObject->transform.RotateAroundAxis(rotationAxis, rotationSpeeed * moveSpeed * Game::instance->time.GetDeltaTime());
		}
	}

	skybox->transform.position(playerCamera->gameObject->transform.position());
}

void Player::Draw()
{
}

void Player::OnCollide(Collider* other)
{
	other->gameObject->transform.SetParent(&gameObject->transform, true);
	m_collidersToDelete.push_back(other);
	other->isEnable = false;
}
