#pragma once
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.h"

using namespace sf;

class Player
{
private:
	// 상수는 const 붙이자.
	const float START_SPEED = 200;
	// 게임시작 초기 체력
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	Vector2f position;
	Vector2f acceleration;

	Sprite sprite;
	Texture texture;

	//해상도 설정
	Vector2i resolution;
	//arena 사이즈?
	IntRect arena;

	int tileSize;
	
	// 어느방향으로 가야하는가
	Vector2f direction;
	// 속도
	float speed;
	float aspeed;
	// 현재 체력
	int health;
	// 현재 최대 체력
	int maxHealth;
	float immuneMs;
	// 피격당한 시간
	Time lastHit;


public:
	// 기본값 설정
	Player();

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

	void GetHealthItem(int amount);

	void UpgradeSpeed();
	void UpgradeMaxHealth();
};