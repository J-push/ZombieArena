#include "Utility.h"

void Utility::SetOrigin(Text& text, Pivots preset)
{
	SetOrigin(text, text.getLocalBounds(), preset);
}

void Utility::SetOrigin(Sprite& sprite, Pivots preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);
}

void Utility::SetOrigin(Shape& shape, Pivots preset)
{
	SetOrigin(shape, shape.getLocalBounds(), preset);
}

void Utility::SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset)
{
	float widthcenter = bounds.width * 0.5f;
	float heightcenter = bounds.height * 0.5f;

	float width = bounds.width;
	float height = bounds.height;


	switch (preset)
	{
	case Pivots::LEFTTOP:
		tr.setOrigin(0.f, 0.f);
		break;
	case Pivots::CENTERTOP:
		tr.setOrigin(widthcenter, 0.f);
		break;
	case Pivots::RIGHTTOP:
		tr.setOrigin(width, 0.f);
		break;
	case Pivots::LEFTCENTER:
		tr.setOrigin(0.f, heightcenter);
		break;
	case Pivots::CENTERCENTER:
		tr.setOrigin(widthcenter, heightcenter);
		break;
	case Pivots::RIGHTCENTER:
		tr.setOrigin(widthcenter, 0.f);
		break;
	case Pivots::LEFTBOTTOM:
		tr.setOrigin(0.f, height);
		break;
	case Pivots::CENTERBOTTOM:
		tr.setOrigin(widthcenter, height);
		break;
	case Pivots::RIGHTBOTTOM:
		tr.setOrigin(width, height);
		break;
	default:
		break;
	}

}
