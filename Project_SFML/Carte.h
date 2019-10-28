#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collectable.h"
#include "box.h"
#include <vector>

using namespace std;

class Carte : public box, public Collectable
{
public :
	sf::Sprite _Sprite;

	Carte();

	Carte(sf::Texture&);

	int imageSize = 100;
	int y;
	int x;
	sf::Sprite getSprite() const;

	//vector <sf::RectangleShape> frontiere;

};

