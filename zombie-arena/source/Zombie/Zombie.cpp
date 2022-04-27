#include "Zombie.h"
#include "../Utility/TextureHolder.h"
#include "../Utility/Utility.h"
#include <iostream>
#include "../Player/Player.h"

std::vector<ZombieInfo> Zombie::zombieInfo;
bool Zombie::isInitInfo = false;

Zombie::Zombie()
{
	if (!isInitInfo)
	{
		zombieInfo.resize((int)ZombieTypes::COUNT);
		{
			auto& info = zombieInfo[(int)ZombieTypes::BLOATER];
			info.type = ZombieTypes::BLOATER;
			info.textureFileName = "graphics/bloater.png";
			info.speed = 40.f;
			info.health = 5;
		}
		{
			auto& info = zombieInfo[(int)ZombieTypes::CHASER];
			info.type = ZombieTypes::CHASER;
			info.textureFileName = "graphics/chaser.png";
			info.speed = 70.f;
			info.health = 1;
		}
		{
			auto& info = zombieInfo[(int)ZombieTypes::CRAWLER];
			info.type = ZombieTypes::CRAWLER;
			info.textureFileName = "graphics/crawler.png";
			info.speed = 20.f;
			info.health = 3;
		}
		isInitInfo = true;
	}
}

bool Zombie::OnHitted()
{
	Player player;
	health -= player.GetPlayerDamage();
	if (health == 0)
	{
		sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));
		zombieState = ZombieState::DEATH;
	}

	return false;
}

bool Zombie::IsAlive()
{
	return ZombieState::ALIVE == zombieState;
}

void Zombie::Normalize(Vector2f& dir)
{
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length != 0)
	{
		dir /= length;
	}
}


void Zombie::Spawn(float x, float y, ZombieTypes type)
{
	zombieState = ZombieState::ALIVE;
	auto &info = zombieInfo[(int)type];
	sprite.setTexture(TextureHolder::GetTexture(info.textureFileName));
	speed = info.speed;
	health = info.health;

	position.x = x;
	position.y = y;

	Utility::SetOrigin(sprite, Pivots::CENTERCENTER);
	sprite.setPosition(position);
}

void Zombie::Update(float dt, Vector2f playerPosition, IntRect arena)
{ 
	switch (zombieState)
	{
	case ZombieState::DEATH:
		deleteBloodTime -= dt;
		if (deleteBloodTime < 0)
		{
			zombieState = ZombieState::DROP;
		}
		return;
	case ZombieState::DROP:
		return;
	}
	//이동
	float h = playerPosition.x - position.x;
	float v = playerPosition.y - position.y;
	Vector2f dir(h, v);
	Normalize(dir);
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

	//회전
	float radian = atan2(playerPosition.y - position.y, playerPosition.x - position.x);
	float degree = radian * 180 / 3.141592f;

	sprite.setRotation(degree);
}

bool Zombie::UpdateCollision(Time time, Player &player)
{
	if (sprite.getGlobalBounds().intersects(player.GetGlobalBound()))
	{
		if (player.OnHitted(time))
		{
			return player.OnHitted(time);
		}
	}

	return false;
}

FloatRect Zombie::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Zombie::GetSprite()
{
	return sprite;
}

void Zombie::Draw(RenderWindow &window)
{
	if (zombieState == ZombieState::ALIVE)
	{
		window.draw(sprite);
	}
	else if (zombieState == ZombieState::DEATH)
	{
		window.draw(sprite);
	}
}