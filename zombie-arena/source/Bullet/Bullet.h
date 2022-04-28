#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Zombie;
class Bullet
{
private:

	const float DEFAULT_SPEED = 2000.f;
	const float DEFAULT_DISTANCE = 1500.f;

	Vector2f position;
	Vector2f direction;
	RectangleShape shape;

	bool isActive;

	float speed;
	float distance;
	std::string textureFileName;
public:
	Bullet();

	//작동하는가?
	void SetActive(bool active);
	void Shoot(Vector2f pos, Vector2f dir);
	void Stop();
	void Update(float dt);
	bool UpdateCollision(const std::vector<Zombie*>& zombies);

	bool IsActive();
	RectangleShape GetShape();

};

