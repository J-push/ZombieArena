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
	// ����� const ������.
	const float START_SPEED = 1000;
	// ���ӽ��� �ʱ� ü��
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	const float DELAY_TIME = 0.5f;
	const int BULLET_NUM = 50;
	const int BULLET_CACHE_SIZE = 1000;
	Vector2f position;
	
	std::string textureFileName;
	Sprite sprite;
	Texture texture;
	//�ػ� ����
	Vector2i resolution;
	//�浹üũ
	IntRect arena;

	int tileSize;
	int BULLETS_IN_GUN = 5;
	int PLAYER_DAMAGE = 1;

	int playerDamage;
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

	//������
	ReloadBar rebar;

	//�� ����
	int highClip;
	//���� ����
	int curClip;

	//źâ ũ��
	int magazineSize;
	std::list<Bullet*> unuseBullets;
	std::list<Bullet*> useBullets;
	float distanceToMuzzle;

	float delaytime;

	bool reloading;
	int haveAmmo;

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