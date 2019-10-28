#include "Collectable.h"

Collectable::Collectable()
{

}

Collectable::Collectable(sf::Texture& TEXTURE_OBJ)
{
	_Sprite.setTexture(TEXTURE_OBJ);
	_Sprite.setPosition(400 - imageSize, 450 - imageSize);
	_Sprite.setPosition(100, 100);
	_Sprite.setScale(0.5f, 0.5f);
}

sf::Sprite Collectable::getSprite() const
{
	return sf::Sprite();
}

