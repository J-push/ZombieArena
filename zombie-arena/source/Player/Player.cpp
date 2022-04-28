#include "Player.h"
#include "../Utility/InputManager.h"
#include <cmath>
#include "../Utility/TextureHolder.h"
#include <iostream>
#include <algorithm>
#include "../../Pickup.h"

Player::Player()
	:speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH), immuneMs(START_IMMUNE_MS),
	arena(), resolution(), tileSize(0.f), textureFileName("graphics/player.png"),
	distanceToMuzzle(0.f)
{

	sprite.setTexture(TextureHolder::GetTexture(textureFileName));
	Utility::SetOrigin(sprite, Pivots::CENTERCENTER);

	for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
	{
		unuseBullets.push_back(new Bullet());
	}
}

Player::~Player()
{
	for (auto bullet : unuseBullets)
	{
		delete bullet;
	}
	unuseBullets.clear();

	for (auto bullet : useBullets)
	{
		delete bullet;
	}
	useBullets.clear();
}

void Player::Shoot(Vector2f dir)
{
	dir = Utility::Normalize(dir);
	Vector2f spawnPos = position + dir * distanceToMuzzle;

	if (unuseBullets.empty())
	{
		for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
		{
			unuseBullets.push_back(new Bullet());
		}
	}

	Bullet* bullet = unuseBullets.front();
	unuseBullets.pop_front();
	useBullets.push_back(bullet);
	bullet->Shoot(spawnPos, dir);
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolution = res;
	this->tileSize = tileSize;

	position.x = arena.width * 0.5f;
	position.y = arena.height * 0.5f;
};

// 플레이어가 피격될 경우 
bool Player::OnHitted(Time timeHit)
{
	// 0.2초 동안은 안맞게
	if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs)
	{
		std::cout << timeHit.asSeconds() << std::endl;
		lastHit = timeHit;
		health -= 10;
		return true;
	}
	return false;
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

//사용자 입력 정보가 필요하다 (update)
void Player::Update(float dt)
{
	// 사용자 입력
	// 플레이어의 방향을 쓸 수 있게 되었다.
	float h = InputManager::GetAxis(Axis::Horizontal);
	float v = InputManager::GetAxis(Axis::Vertical);
	Vector2f dir(h, v);

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	if (length > 1) // 키입력이 있을 떄
	{
		dir /= length;
	}
	// 이동
	position += dir * speed * dt;
	sprite.setPosition(position);

	if (position.x < arena.left + 50 + 25)
	{
		position.x = arena.left + 50 + 25;
	}
	else if (position.x > arena.width - 50 - 25)
	{
		position.x = arena.width - 50 - 25;
	}
	else if (position.y < arena.top + 50 + 25)
	{
		position.y = arena.top + 50 + 25;
	}
	else if (position.y > arena.height - 50 - 25)
	{
		position.y = arena.height - 50 - 25;
	}

	// 회전
	Vector2i mousePos = InputManager::GetMousePosition();
	Vector2i mouseDir;
	mouseDir.x = mousePos.x - resolution.x * 0.5f;
	mouseDir.y = mousePos.y - resolution.y * 0.5f;
	sprite.setPosition(position);

	float radian = atan2(mouseDir.y, mouseDir.x);
	float degree = radian * 180 / 3.141592f;

	sprite.setRotation(degree);

	timer -= dt;

	if (InputManager::GetMouseButton(Mouse::Button::Left))
	{
		if (timer < 0)
		{
			Shoot(Vector2f(mouseDir.x, mouseDir.y));
			timer = DELAY_TIMER;
		}
	}

	// end , begin 처음부터 끝까지 순회하는것
	// rend , rbegin 뒤에서부터 순회하는것
	// 
	// 발사체
	auto it = useBullets.begin();
	while (it != useBullets.end())
	{
		Bullet* bullet = *it;
		bullet->Update(dt);

		if (!bullet->IsActive())
		{
			it = useBullets.erase(it);
			unuseBullets.push_back(bullet);
		}
		else
		{
			++it;
		}
	}
}

bool Player::UpdateCollision(const std::list<Pickup*> &items)
{
	FloatRect bounds = sprite.getGlobalBounds();
	bool isCollided = false;

	for (auto item : items)
	{
		if (bounds.intersects(item->GetGlobalBounds()))
		{
			item->GotIt();
		}
		isCollided = true;
	}
	return isCollided;
}

bool Player::UpdateCollision(const std::vector<Zombie *> &zombies)
{
	bool isCollided = false;

	for (auto bullet : useBullets)
	{
		if (bullet->UpdateCollision(zombies))
		{
			isCollided = true;
		}
	}

	return isCollided;
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
	for (auto bullet : useBullets)
	{
		window.draw(bullet->GetShape());
	}
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
