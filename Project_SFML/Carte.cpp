#include "Carte.h"

Carte::Carte()
{
	if (!boxTexture.loadFromFile("box.png"))
	{
		cout << "Texture error" << endl;
	}


	// f pour mur
	// l pour lave
	// b pour brique
	// t pour tacos
	rawDecor = {
		"ffffffff",
		"f_b____f",
		"fllllllf",
		"f__l___f",
		"f____b_f",
		"f______f",
		"f___t__f",
		"ft____bf",
		"ffffffff",
	};

	Niveau niv;
	Box box;
	box._Sprite.setTexture(boxTexture);
	for (size_t y = 0; y < 9; y++)
	{
		for (size_t x = 0; x < 8; x++)
		{
			niv.decor[x][y] = rawDecor[y][x];
			cout << niv.decor[x][y];

			if (niv.decor[x][y] == "b") {
				box._Sprite.setPosition(x * 100, y * 100);
				niv.boxx.push_back(box);
			}

		}
		cout << endl;
	}
	niveaux.push_back(niv);
}

bool Carte::tilemap_get_at_pixel(sf::Vector2i pos)
{
	sf::Vector2i tile;
	tile.x = pos.x / 100;
	tile.y = pos.y / 100;
	if (niveaux[niveau_actuel].decor[tile.x][tile.y] == "f" || niveaux[niveau_actuel].decor[tile.x][tile.y] == "l") {
		return true;
	}
	return false;
}
