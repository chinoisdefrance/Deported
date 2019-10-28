#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Ennemis.h"

using namespace std;

class Projectile{
private:
	sf::Vector2f direction;
public:

	Projectile();
	Projectile(int x, int y, int hori, int verti);
	void update();
	sf::Sprite sprite;

};

