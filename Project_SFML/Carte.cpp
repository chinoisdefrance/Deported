#include "Carte.h"

Carte::Carte()
{
//assignement de textures pour les tableaux de vecteur
	//texture box
	if (!boxTexture.loadFromFile("images/box.png"))
	{
		cout << "Texture error" << endl;
	}
	//texture pinatas
	if (!pinataTexture.loadFromFile("images/pinata.png"))
	{
		cout << "Texture error" << endl;
	}
	//texture mexicains
	if (!mexicanTexture.loadFromFile("images/mexican.png"))
	{
		cout << "Texture error" << endl;
	}

//lettres assign�s aux �l�ments du d�cor

	// f pour mur
	// l pour lave
	// b pour brique
	// c pour box
	// t pour tacos
	// p pour pinatas
	// m pour mexicans
	// h pour coffre
	// d pour door

	//premier niveau
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
	//deuxi�me niveau
	rawDecors.push_back(rawDecor);
	vector<string> rawDecor1 = {
		"ffffffff",
		"fmbt__df",
		"fll____f",
		"fpl_c__f",
		"fbl___pf",
		"f_l_c__f",
		"fll_t_bf",
		"fm____hf",
		"ffffffff",
	};

	rawDecors.push_back(rawDecor1);
	//permet de changer de niveau, d'afficher les diff�rents niveaux
	for (size_t i = 0; i < rawDecors.size(); i++)
	{


		Niveau niv;
		Box box;
		box._Sprite.setTexture(boxTexture);

		Ennemis ennemis;
		niv.coffreOuvert = false;
		for (size_t y = 0; y < 9; y++)
		{
			for (size_t x = 0; x < 8; x++)
			{
				niv.decor[x][y] = rawDecors[i][y][x];
				//boxs
				if (niv.decor[x][y] == "c") {
					box._Sprite.setPosition(x * 100, y * 100);
					niv.boxx.push_back(box);
				}
				//pinatas
				else if (niv.decor[x][y] == "p") {
					ennemis._Sprite.setTexture(pinataTexture);
					ennemis._Sprite.setPosition(x * 100, y * 100);
					niv.Pinatas.push_back(ennemis);
				}
				//mexicains
				else if (niv.decor[x][y] == "m") {
					ennemis._Sprite.setTexture(mexicanTexture);
					ennemis._Sprite.setPosition(x * 100, y * 100);
					niv.Mexicans.push_back(ennemis);
				}
			}
		}

		niveaux.push_back(niv);
	}
}
//le joueur est bloqu� par certains �l�ments du d�cor
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
