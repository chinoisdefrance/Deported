#include "Carte.h"

Carte::Carte()
{

}

Carte::Carte(sf::Texture& TEXTURE_MAP)
{
	_Sprite.setTexture(TEXTURE_MAP);
}

sf::Sprite Carte::getSprite() const
{
	return sf::Sprite();
}

