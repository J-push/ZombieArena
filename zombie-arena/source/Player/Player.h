#pragma once
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.h"

using namespace sf;

class Player
{
private:
	// ����� const ������.
	const float START_SPEED = 500;
	// ���ӽ��� �ʱ� ü��
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	Vector2f position;
	
	std::string textureFileName;
	Sprite sprite;
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
	// �ǰݴ��� �ð�
	Time lastHit;

public:
	// �⺻�� ����
	Player();

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

	void GetHealthItem(int amount);

	void UpgradeSpeed();
	void UpgradeMaxHealth();
};