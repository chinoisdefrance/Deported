#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "box.h"
#include "Ennemis.h"

using namespace std;

struct Niveau
{
	string decor[8][9];
	vector<Box> boxx;
	vector<Ennemis> Pinatas;
	vector<Ennemis> Mexicans;
	bool haveKey = false;
	int briquesCount = 0;
	int tweetCount = 20;
	bool coffreOuvert;
};



class Carte
{
public:
	Carte();
	vector<vector<string>> rawDecors;
	bool tilemap_get_at_pixel(sf::Vector2i pos, bool bloqueSol);

	vector<Niveau> niveaux;
	int niveau_actuel = 0;
	sf::Texture boxTexture;
	sf::Texture pinataTexture;
	sf::Texture mexicanTexture;

};

