#include "Carte.h"

Carte::Carte()
{

	// f pour mur
	// l pour lave
	// b pour brique
	// t pour tacos
	rawDecor = {
		"ffffffff",
		"f_b____f",
		"f_____bf",
		"f__l___f",
		"f__l_b_f",
		"f______f",
		"f____t_f",
		"ft_____f",
		"ffffffff",
	};
	for (size_t y = 0; y < 9; y++)
	{
		for (size_t x = 0; x < 8; x++)
		{
			decor[x][y] = rawDecor[y][x];
			cout << decor[x][y];
		}
		cout << endl;
	}
}

bool Carte::tilemap_get_at_pixel(sf::Vector2i pos)
{
	sf::Vector2i tile;
	tile.x = pos.x / 100;
	tile.y = pos.y / 100;
	if (decor[tile.x][tile.y] == "f") {
		return true;
	}
	return false;
}
