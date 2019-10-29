#pragma once
#include <SFML/Graphics.hpp>
#include "Carte.h"

class Collision
{
public:

	/// <summary>
	/// gestion des collisions entre un sprite et une tile inspiré par https://www.youtube.com/watch?v=sGm8LZJXSIg
	/// </summary>
	/// <param name="offsetX">offset x.</param>
	/// <param name="offsetY">offset y.</param>
	/// <param name="mobileObject">l'objet qui se deplace</param>
	/// <param name="room">la piece actuel </param>
	/// <param name="center">si definie a <c>true</c> on centre la collision</param>
	/// <param name="reduction">reduction de la zone de collision <b>0</b> par defaut</param>
	/// <returns></returns>
	static bool tile_place_meeting(int offsetX, int offsetY, sf::Sprite mobileObject, Carte& room, bool center = false, int reduction = 0);

	/// <summary>
	/// verification de collision entre un obj qui se deplace et un obj fix
	/// </summary>
	/// <param name="moving">Sprite/RectangleShape de l'object se deplaçant.</param>
	/// <param name="fix">Sprite de l'object fix.</param>
	/// <param name="hori">decalage horizontale.</param>
	/// <param name="verti">decalage verticale.</param>
	/// <returns><b>true</b> si collision</returns>
	static bool mob_place_meeting(sf::Sprite moving, sf::Sprite fix, int hori = 0, int verti = 0);
	static bool mob_place_meeting(sf::RectangleShape moving, sf::Sprite fix, int hori = 0, int verti = 0);
};