#pragma once

#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;
using namespace std;

enum class Pivots
{
	// LC , RC 
	// TC , BC
	// L , R, C
	// T , B
	LEFTTOP,
	CENTERTOP,
	RIGHTTOP,
	LEFTCENTER,
	CENTERCENTER,
	RIGHTCENTER,
	LEFTBOTTOM,
	CENTERBOTTOM,
	RIGHTBOTTOM,
};


class Utility
{
private:
	static random_device rd;
	static mt19937 gen;

public:
	static void SetOrigin(Text& text, Pivots preset);
	static void SetOrigin(Sprite& sprite, Pivots preset);
	static void SetOrigin(Shape& shape, Pivots preset);

	static void SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset);

	static int RandomRange(int min, int exclueMax);

	static float GetLength(const Vector2f& vector);
	static Vector2f Normalize(Vector2f& vector);
	static float GetAngle(const Vector2f& from, const Vector2f& to);
};