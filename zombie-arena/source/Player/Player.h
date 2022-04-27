#pragma once
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.h"
#include "../Bullet/Bullet.h"
#include <list>
#include "../../ReloadBar.h"

using namespace sf;

class Pickup;

class Player
{
private:
	// 상수는 const 붙이자.
	const float START_SPEED = 1000;
	// 게임시작 초기 체력
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	const float DELAY_TIME = 0.5f;
	const int BULLET_NUM = 50;
	const int BULLET_CACHE_SIZE = 1000;
	Vector2f position;
	
	std::string textureFileName;
	Sprite sprite;
	Texture texture;
	//해상도 설정
	Vector2i resolution;
	//충돌체크
	IntRect arena;

	int tileSize;
	int BULLETS_IN_GUN = 5;
	int PLAYER_DAMAGE = 1;

	int playerDamage;
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

	//재장전
	ReloadBar rebar;

	//총 개수
	int highClip;
	//현재 개수
	int curClip;

	//탄창 크기
	int magazineSize;
	std::list<Bullet*> unuseBullets;
	std::list<Bullet*> useBullets;
	float distanceToMuzzle;

	float delaytime;

	bool reloading;
	int haveAmmo;

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

	int GetHealth();
	int GetMaxHealth();
	int GetClip();
	int GetClipSum();
	int GetPlayerDamage() const;

	void Update(float dt);
	bool UpdateCollision(const std::list<Pickup*> &items);
	bool UpdateCollision(const std::vector<Zombie *> &zombies);
	void Draw(RenderWindow& window);

	void GetHealthItem(int amount);

	void UpgradeSpeed();
	void UpgradeMaxHealth();

	void SetBul(int bul);
	void SetHiBul(int bul);

	void SetHealth();
	void SetMaxHealth();
	void SetSpeed();
	void InitHealth();
};