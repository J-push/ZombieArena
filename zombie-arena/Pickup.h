#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum class PickupTypes
{
    Ammo,
    Health,
};

class Pickup
{
private:
    int HEALTH_START_VALUE = 50;
    int AMMO_START_VALUE = 12;
    const float START_WAIT_TIME = 10.f;
    const float START_SECONDS_FOR_LIVE = 5.f;

    PickupTypes type;

    Sprite sprite;
    IntRect arena;

    int value;
    bool earnIt;

    bool spawned;
    float timer;

public:
    Pickup();
    Pickup(PickupTypes type);

    void Update(float dt);

    void Spawn(bool spawn);
    int GotIt();

    void SetArena(IntRect rect);
    void SetEarnIt();
    void SetHealthValue();
    void SetAmmoValue();

    Sprite GetSprite();
    FloatRect GetGlobalBounds();
    PickupTypes GetType();

    bool IsSpawned();
    bool GetEarnIt() const;

};

