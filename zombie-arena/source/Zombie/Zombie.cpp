#include "Zombie.h"
#include "../Utility/TextureHolder.h"
#include "../Utility/Utility.h"

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
	// 나중에
	return false;
}

bool Zombie::IsAlive()
{
	return false;
}

void Zombie::Spawn(float x, float y, ZombieTypes type)
{
	auto& info = zombieInfo[(int)type];
	sprite.setTexture(TextureHolder::GetTexture(info.textureFileName));
	speed = info.speed;
	health = info.health;

	position.x = x;
	position.y = y;

	Utility::SetOrigin(sprite, Pivots::CENTERCENTER);
	sprite.setPosition(position);
}

void Zombie::Update(float dt, Vector2f playerPosition)
{
	// 숙제
	//좀비에서 플레이어로 가는 방향을 구해라 
    //정규화해라.
	//이동량이 나오면 더해줘라 
	float h = playerPosition.x - position.x;
	float v = playerPosition.y - position.y;
	Vector2f dir(h, v);
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length != 0)
	{
		dir /= length;
	}
	position += dir * speed * dt;
	sprite.setPosition(position);

	float radian = atan2(playerPosition.y - position.y, playerPosition.x - position.x);
	float degree = radian * 180 / 3.141592f;

	sprite.setRotation(degree);
}

FloatRect Zombie::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Zombie::GetSprite()
{
	return sprite;
}
