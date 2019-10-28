#include "Ennemis.h"

Ennemis::Ennemis()
{
}

Ennemis::Ennemis(sf::Texture& TEMP_ENNEMIS)
{
	ptVieEnnemis = 1;
	_Sprite.setTexture(TEMP_ENNEMIS);
	_Sprite.setPosition(400 - imageSize, 450 - imageSize);
	_Sprite.setPosition(0, 0);
	_Sprite.setScale(1.0f, 1.0f);
}

sf::Sprite Ennemis::getSPrite() const
{
	return sf::Sprite();
}

void Ennemis::ennemisTakeDamage(int damage)
{
	ptVieEnnemis -= damage;
	cout << ptVieEnnemis << endl;
	//_Sprite.setColor(sf::Color::Red);
	ennemisHaveTakeDamage = true;
	if (ptVieEnnemis <= 0) 
	{
		isMort = true;
		damage = 0;
	}
	
}
