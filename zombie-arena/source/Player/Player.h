#pragma once
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.h"
#include "../Bullet/Bullet.h"
#include <list>

using namespace sf;

class Pickup;

class Player
{
private:
	// 상수는 const 붙이자.
	const float START_ACCEL = 2000;
	const float START_SPEED = 1000;
	// 게임시작 초기 체력
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;
	const float DELAY_TIMER = 0.3f;
	Vector2f position;
	
	std::string textureFileName;
	Sprite sprite;
	Sprite bullet;
	Texture texture;

	//해상도 설정
	Vector2i resolution;
	//충돌체크
	IntRect arena;

	int tileSize;
	
	// 속도
	float speed;

	// 가속도
	float curSpeed;
	float accel;

	// 현재 체력
	int health;
	// 현재 최대 체력
	int maxHealth;
	float immuneMs;
	bool immune;
	// 피격당한 시간
	Time lastHit;

	float timer;

	const int BULLET_CACHE_SIZE = 1000;
	std::list<Bullet*> unuseBullets;
	std::list<Bullet*> useBullets;
	float distanceToMuzzle;

public:
	// 기본값 설정
	Player();
	~Player();

	void Shoot(Vector2f dir);

	void Spawn(IntRect arena, Vector2i res, int tileSize);

	//피격당할 떄 
	bool OnHitted(Time timeHit);

	Time GetLastTime() const;
	FloatRect GetGlobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int GetHealth() const;
	// x y 요소가 int라서 2i
	void Update(float dt);
	bool UpdateCollision(const std::list<Pickup*> &items);
	bool UpdateCollision(const std::vector<Zombie *> &zombies);
	void Draw(RenderWindow& window);

	void GetHealthItem(int amount);

	void UpgradeSpeed();
	void UpgradeMaxHealth();
};