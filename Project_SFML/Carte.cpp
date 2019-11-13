#include "Carte.h"

Carte::Carte()
{
	if (!boxTexture.loadFromFile("box.png"))
	{
		cout << "Texture error" << endl;
	}

	if (!pinataTexture.loadFromFile("pinata.png"))
	{
		cout << "Texture error" << endl;
	}

	if (!mexicanTexture.loadFromFile("mexican.png"))
	{
		cout << "Texture error" << endl;
	}


	// f pour mur
	// l pour lave
	// b pour brique
	// c pour box
	// t pour tacos
	// p pour pinatas
	// m pour mexicans
	// h pour coffre
	// d pour door
	vector<string> rawDecor = {
		"ffffffff",
		"f_b__mdf",
		"fllllllf",
		"f__l__hf",
		"f_c__b_f",
		"f_p___mf",
		"f_c_t__f",
		"ft_p__bf",
		"ffffffff",
	};

	rawDecors.push_back(rawDecor);
	vector<string> rawDecor1 = {
		"ffffffff",
		"f_____df",
		"f______f",
		"f_____hf",
		"f_c____f",
		"f_p____f",
		"f_c_t__f",
		"ft_p___f",
		"ffffffff",
	};

	rawDecors.push_back(rawDecor1);
	for (size_t i = 0; i < rawDecors.size(); i++)
	{


		Niveau niv;
		Box box;
		box._Sprite.setTexture(boxTexture);

		Ennemis ennemis;

		for (size_t y = 0; y < 9; y++)
		{
			for (size_t x = 0; x < 8; x++)
			{
				niv.decor[x][y] = rawDecors[i][y][x];
				cout << niv.decor[x][y];

				if (niv.decor[x][y] == "c") {
					box._Sprite.setPosition(x * 100, y * 100);
					niv.boxx.push_back(box);
				}
				else if (niv.decor[x][y] == "p") {
					ennemis._Sprite.setTexture(pinataTexture);
					ennemis._Sprite.setPosition(x * 100, y * 100);
					niv.Pinatas.push_back(ennemis);
				}
				else if (niv.decor[x][y] == "m") {
					ennemis._Sprite.setTexture(mexicanTexture);
					ennemis._Sprite.setPosition(x * 100, y * 100);
					niv.Mexicans.push_back(ennemis);
				}
			}
			cout << endl;
		}

		niveaux.push_back(niv);
	}
}

bool Carte::tilemap_get_at_pixel(sf::Vector2i pos, bool bloqueSol = false)
{
	sf::Vector2i tile;
	tile.x = pos.x / 100;
	tile.y = pos.y / 100;
	if (niveaux[niveau_actuel].decor[tile.x][tile.y] == "f" || (bloqueSol && niveaux[niveau_actuel].decor[tile.x][tile.y] == "l")) {
		return true;
	}
	return false;
}
