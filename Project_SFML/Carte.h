#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Carte
{
public:
	Carte();
	vector<string> rawDecor;
	string decor[8][9];
	bool tilemap_get_at_pixel(sf::Vector2i pos);
};

