#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Player;

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

	//�浹üũ
	IntRect arena;

	float speed;
	float health;

	bool alive;

	//instance static ��������� �ʱ�ȭ �Ұ�.
	static std::vector<ZombieInfo> zombieInfo;
	static bool isInitInfo;

public:
	Zombie();

	bool OnHitted();
	bool IsAlive();
	void Normalize(Vector2f& dir);
	void Spawn(float x, float y, ZombieTypes type, IntRect arena);
	void Update(float dt, Vector2f playerPosition);

	bool UpdateCollision(Time time, Player &player);


	FloatRect GetGlobalBound();
	Sprite GetSprite();
};

