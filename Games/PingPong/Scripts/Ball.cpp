#include "Ball.h"

#include "Player.h"

void Ball::Awake()
{
	RenderComponent* rend = new RenderComponent;
	rend->shaderPath = L"./Shaders/MyVeryFirstShader.hlsl";
	rend->mesh = Basic::Box2D::Create(0.05f, 0.05f);
	gameObject->AddComponent(*rend);

	BoxCollider* ballCollider = new BoxCollider;
	ballCollider->size = { 0.05f, 0.05f };
	col = ballCollider;
	gameObject->AddComponent(*ballCollider);
}



static void printGameScore() {
	std::system("cls");
	std::cout <<
		((PingPongGame*)PingPongGame::instance)->player1->score
		<< " - " <<
		((PingPongGame*)PingPongGame::instance)->player2->score
		<< std::endl;
}
void Ball::Update()
{
	gameObject->transform.position.x += velocity.x * Time::instance->GetDeltaTime();
	gameObject->transform.position.y += velocity.y * Time::instance->GetDeltaTime();

	if (gameObject->transform.position.y <= -0.975f) {
		velocity.y = -velocity.y;
	}
	if (gameObject->transform.position.y >= 0.975f) {
		velocity.y = -velocity.y;
	}

	BoxCollider* res;
	if (col->IsCollided(&res)) {
		bool dirSign = std::signbit(res->gameObject->transform.position.x - gameObject->transform.position.x);
		bool velSign = std::signbit(velocity.x);
		if (dirSign == velSign) {
			float distY = gameObject->transform.position.y - res->gameObject->transform.position.y;
			float signY = std::signbit(velocity.y);
			float reflection = (0.5f * res->size.y + signY * distY) / res->size.y;
			float currentSpeed = velocity.Length();
			SMath::Vector2 up = { 0,1 };

			velocity.x = -1.0f * velocity.x;
			velocity = velocity + up * distY * spread + reflection * res->velocity * friction;
			velocity.Normalize();
			velocity = velocity * currentSpeed * speed_increase;

			if (velocity.Length() > max_speed) {
				velocity.Normalize();
				velocity = velocity * max_speed;
			}
		}
	}

	if (gameObject->transform.position.x < -1)
	{
		((PingPongGame*)PingPongGame::instance)->player2->score++;
		printGameScore();
		((PingPongGame*)PingPongGame::instance)->Restart();
	}
	if (gameObject->transform.position.x > 1) 
	{
		((PingPongGame*)PingPongGame::instance)->player1->score++;
		printGameScore();
		((PingPongGame*)PingPongGame::instance)->Restart();
	}
}


void Ball::DestroyResources()
{
}

void Ball::Reload()
{
}

void Ball::Start()
{
}
