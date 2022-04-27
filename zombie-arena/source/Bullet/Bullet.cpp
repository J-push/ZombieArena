#include "Bullet.h"
#include "../Utility/Utility.h"
#include "../Utility/TextureHolder.h"
#include "../Zombie/Zombie.h"

Bullet::Bullet()
	:speed(DEFAULT_SPEED), isActive(false), distance(DEFAULT_DISTANCE)
{
	shape.setSize(Vector2f(30, 10));
	Utility::SetOrigin(shape, Pivots::CENTERCENTER);
}

void Bullet::SetActive(bool active)
{
	isActive = active;
}

bool Bullet::IsActive()
{
	return isActive;
}

void Bullet::Shoot(Vector2f pos, Vector2f dir)
{
	SetActive(true);
	distance = 0.f;
	position = pos;
	shape.setPosition(position);
	direction = Utility::Normalize(dir);
	float degree = Utility::GetAngle(position, position + direction);
	shape.setRotation(degree);
}

void Bullet::Stop()
{
	SetActive(false);
}


void Bullet::Update(float dt)
{
	position += direction * speed * dt;
	shape.setPosition(position);

	distance += speed * dt;
	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
}

bool Bullet::UpdateCollision(const std::vector<Zombie *> &zombies)
{
	FloatRect bounds = shape.getGlobalBounds();

	for (auto zombie : zombies)
	{
		//살아있는 좀비
		if (zombie->IsAlive())
		{
			if (bounds.intersects(zombie->GetGlobalBound()))
			{
				zombie->OnHitted();
				Stop();

				return true;
			}
		}
	}
	return false;
}

RectangleShape Bullet::GetShape()
{
	return shape;
}