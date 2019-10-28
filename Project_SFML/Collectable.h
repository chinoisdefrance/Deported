#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Collectable
{
public: 
	sf::Sprite _Sprite;

	Collectable();
	Collectable(sf::Texture&);

	int imageSize = 100;

	sf::Sprite getSprite() const;

	

};

