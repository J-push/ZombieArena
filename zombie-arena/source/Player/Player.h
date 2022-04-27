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
	// ����� const ������.
	const float START_ACCEL = 2000;
	const float START_SPEED = 1000;
	// ���ӽ��� �ʱ� ü��
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;
	const float DELAY_TIMER = 0.3f;
	Vector2f position;
	
	std::string textureFileName;
	Sprite sprite;
	Sprite bullet;
	Texture texture;

	//�ػ� ����
	Vector2i resolution;
	//�浹üũ
	IntRect arena;

	int tileSize;
	
	// �ӵ�
	float speed;

	// ���ӵ�
	float curSpeed;
	float accel;

	// ���� ü��
	int health;
	// ���� �ִ� ü��
	int maxHealth;
	float immuneMs;
	bool immune;
	// �ǰݴ��� �ð�
	Time lastHit;

	float timer;

	const int BULLET_CACHE_SIZE = 1000;
	std::list<Bullet*> unuseBullets;
	std::list<Bullet*> useBullets;
	float distanceToMuzzle;

public:
	// �⺻�� ����
	Player();
	~Player();

	void Shoot(Vector2f dir);

	void Spawn(IntRect arena, Vector2i res, int tileSize);

	//�ǰݴ��� �� 
	bool OnHitted(Time timeHit);

	Time GetLastTime() const;
	FloatRect GetGlobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int GetHealth() const;
	// x y ��Ұ� int�� 2i
	void Update(float dt);
	bool UpdateCollision(const std::list<Pickup*> &items);
	bool UpdateCollision(const std::vector<Zombie *> &zombies);
	void Draw(RenderWindow& window);

	void GetHealthItem(int amount);

	void UpgradeSpeed();
	void UpgradeMaxHealth();
};