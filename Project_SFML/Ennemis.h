#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Ennemis
{
public:
	sf::Sprite _Sprite;
	sf::Sprite getSPrite() const;
	bool isMort =false;
	Ennemis();
	Ennemis(sf::Texture&);

	int imageSize = 100;
	int ptVieEnnemis = 1;

	bool ennemisHaveTakeDamage = false;
	
	void ennemisTakeDamage(int damage);
};

