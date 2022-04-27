#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class ReloadBar 
{
private:
	const float RELOAD_TIME = 1.f;
	const int MAGAZINE = 25;
	RectangleShape timebar;
	float timeToReload;
	int leftBullet;
	//Player player;
public:
	ReloadBar();
	void Update(Vector2f playerPos, float dt);
	void Reload(float dt);
	
	RectangleShape &GetShape();

	float GetBar();
	void SetBer();
};