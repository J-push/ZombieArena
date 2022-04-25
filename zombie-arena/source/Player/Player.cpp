#include "Player.h"
#include "../Utility/InputManager.h"
#include "../Utility/Utility.h"
#include <cmath>

Player::Player()
	:speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH), immuneMs(START_IMMUNE_MS),
	arena(), resolution(), tileSize(0.f), aspeed(0.3f)
{
	texture.loadFromFile("graphics/player.png");
	sprite.setTexture(texture);

	Utility::SetOrigin(sprite, Pivots::CENTERCENTER);
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolution = res;
	this->tileSize = tileSize;

	position.x = arena.width * 0.5f;
	position.y = arena.height * 0.5f;
};

// �÷��̾ �ǰݵ� ��� 
bool Player::OnHitted(Time timeHit)
{
	if (timeHit.asMicroseconds() - lastHit.asMicroseconds() > immuneMs)
	{
		lastHit = timeHit;
		health -= 10;
		return true;
	}

	return true;
};

Time Player::GetLastTime() const
{
	return lastHit;
}

FloatRect Player::GetGlobalBound() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return position;
}

float Player::GetRotation() const
{
	return sprite.getRotation();
}

Sprite Player::GetSprite() const
{
	return sprite;
}

int Player::GetHealth() const
{
	return health;
}

//����� �Է� ������ �ʿ��ϴ� (update)
void Player::Update(float dt)
{
	// ����� �Է�
	// �÷��̾��� ������ �� �� �ְ� �Ǿ���.
	direction.x = InputManager::GetAxis(Axis::Horizontal);
	direction.y = InputManager::GetAxis(Axis::Vertical);
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
	{
		direction /= length;
	}
	// �̵�
	position += direction * speed * dt;
	speed += aspeed;
	// ȸ��
	Vector2i mousePos = InputManager::GetMousePosition();
	Vector2i mouseDir;
	//resolution -> �ػ� �߾�
	/*mouseDir.x = mousePos.x - resolution.x * 0.5f;
	mouseDir.y = mousePos.y - resolution.y * 0.5f;*/
	mouseDir.x = mousePos.x - position.x;
	mouseDir.y = mousePos.y - position.y;
	sprite.setPosition(position);

	float radian = atan2(mouseDir.y, mouseDir.x);
	float degree = radian * 180 / 3.141592f;

	sprite.setRotation(degree);
}

void Player::GetHealthItem(int amount)
{
	health += amount;
	if (health > maxHealth)
	{
		health = maxHealth;
	}
	if (health < 0)
	{
		health = 0;
	}
}

void Player::UpgradeSpeed()
{
	speed += START_SPEED * 0.2f;
}

void Player::UpgradeMaxHealth()
{
	maxHealth += START_HEALTH * 0.2f;
}
