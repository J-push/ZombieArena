#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

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
public:
	static void SetOrigin(Text& text, Pivots preset);
	static void SetOrigin(Sprite& sprite, Pivots preset);
	static void SetOrigin(Shape& shape, Pivots preset);

	static void SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset);
};