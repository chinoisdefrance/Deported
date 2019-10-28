#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class box
{
public:

	sf::Sprite _Sprite;

	box();
	box(sf::Texture&);

	int imageSize = 100;

	sf::Sprite getSPrite() const;

};

