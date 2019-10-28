#include "box.h"

box::box()
{

}

box::box(sf::Texture& TEMP_BOX)
{
	_Sprite.setTexture(TEMP_BOX);
	_Sprite.setPosition(400 - imageSize, 450 - imageSize);
	_Sprite.setPosition(0, 0);
	_Sprite.setScale(0.3f, 0.3f);
}

sf::Sprite box::getSPrite() const
{
	return sf::Sprite();
}
