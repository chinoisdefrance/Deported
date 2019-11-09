#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "box.h"

using namespace std;

struct Niveau
{
	string decor[8][9];
	vector<Box> boxx;
};



class Carte
{
public:
	Carte();
	vector<string> rawDecor;
	bool tilemap_get_at_pixel(sf::Vector2i pos);

	vector<Niveau> niveaux;
	int niveau_actuel = 0;
	sf::Texture boxTexture;

};

