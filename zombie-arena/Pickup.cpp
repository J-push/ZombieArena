#include "Pickup.h"
#include "source/Utility/TextureHolder.h"
#include "source/Utility/Utility.h"

Pickup::Pickup() : HEALTH_START_VALUE(50), AMMO_START_VALUE(12)
{
}


Pickup::Pickup(PickupTypes type)
	:type(type)
{
	std::string textureId;
	switch (this->type)
	{
	case PickupTypes::Ammo:
		textureId = "graphics/ammo_pickup.png";
		value = AMMO_START_VALUE;
		break;
	case PickupTypes::Health:
		textureId = "graphics/health_pickup.png";
		value = HEALTH_START_VALUE;
		break;
	}
	sprite.setTexture(TextureHolder::GetTexture(textureId));
	Utility::SetOrigin(sprite, Pivots::CENTERCENTER);

	Spawn(false);
}

void Pickup::Update(float dt)
{
	timer -= dt;
	if (timer < 0)
	{
		Spawn(!spawned);
	}
}

void Pickup::Spawn(bool spawn)
{
	spawned = spawn; // ÃÊ±âÈ­
	if (spawned)
	{
		timer = START_SECONDS_FOR_LIVE;

		int x = Utility::RandomRange(arena.left, arena.left + arena.width);
		int y = Utility::RandomRange(arena.top, arena.top + arena.height);

		sprite.setPosition(Vector2f(x, y));
		earnIt = true;
	}
	else
	{
		timer = START_WAIT_TIME;
	}
}

int Pickup::GotIt()
{
	return value;
}

void Pickup::SetArena(IntRect rect)
{
	arena = rect;
}

bool Pickup::IsSpawned()
{
	return spawned;
}

Sprite Pickup::GetSprite()
{
	return sprite;
}

FloatRect Pickup::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

PickupTypes Pickup::GetType()
{
	return type;
}

bool Pickup::GetEarnIt() const
{
	return earnIt;
}

void Pickup::SetHealthValue()
{
	HEALTH_START_VALUE += 100;
}

void Pickup::SetAmmoValue()
{
	AMMO_START_VALUE += 20;
}

void Pickup::SetEarnIt()
{
	earnIt = false;
}