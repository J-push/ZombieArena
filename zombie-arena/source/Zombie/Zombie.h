#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

enum class ZombieTypes
{
	BLOATER,
	CHASER,
	CRAWLER,
	COUNT,
};

struct ZombieInfo
{
	ZombieTypes type;
	std::string textureFileName;
	float speed;
	int health;

};

class Zombie
{
private:
	ZombieTypes zombieType;

	Vector2f position;
	Sprite sprite;
	
	float speed;
	float health;

	bool alive;

	//instance static 멤버변수는 초기화 할것.
	static std::vector<ZombieInfo> zombieInfo;
	static bool isInitInfo;

public:
	Zombie();

	bool OnHitted();
	bool IsAlive();
	void Spawn(float x, float y, ZombieTypes type);
	void Update(float dt, Vector2f playerPosition);

	FloatRect GetGlobalBound();
	Sprite GetSprite();
};

