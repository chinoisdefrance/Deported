#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <cmath>
#include"Collision.h"
#include "Player.h"
#include "Carte.h"
#include "Collectable.h"
#include "Ennemis.h"
#include "box.h"
#include "Projectiles.h"

#define COLLISION_H

using namespace std;


int main()
{
	const int CaseTaille = 100;

	int briquesCount = 0;
	int tacosCount = 0;
	bool invincible;

	int horizontal = 0;
	int vertical = 0;

	sf::Vector2f playerCenter;
	vector<Projectile> projectiles;
	sf::Sprite pinata_broken;

	//D�finir dimensions fen�tre et musique)

	sf::RenderWindow window(sf::VideoMode(800, 900), "SFML works!");
	window.setKeyRepeatEnabled(false);
	sf::Music music;
	sf::Clock clockInvincible;

	sf::RectangleShape cactus(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape sol(sf::Vector2f(800.0f, 900.0f));
	sf::RectangleShape lave(sf::Vector2f(100.0f, 100.0f));


	//D�finir textures 

	sf::Texture playerTexture;
	sf::Texture briqueTexture;
	sf::Texture pinataTexture;
	sf::Texture cactusTexture;
	sf::Texture solTexture;
	sf::Texture mexicanTexture;
	sf::Texture tacosTexture;
	sf::Texture boxTexture;
	sf::Texture hatTexture;
	sf::Texture pinata_brokenTexture;
	sf::Texture laveTexture;
	sf::Texture t_projectile;

	//Rechercher textures dans doc

	solTexture.loadFromFile("sable.jpg");
	cactusTexture.loadFromFile("cactus.png");
	laveTexture.loadFromFile("lave.jpg");
	t_projectile.loadFromFile("twitter.png");
	pinata_brokenTexture.loadFromFile("broken-pinata.png");
	hatTexture.loadFromFile("mexican_hat.png");
	//MUSIC//

	if (!music.openFromFile("Jarabes.ogg"))
	{
		return -1;
	}
	music.play();

	//FIN MUSIC//

	//Appliquer Textures

	cactus.setTexture(&cactusTexture);
	sol.setTexture(&solTexture);
	lave.setTexture(&laveTexture);

	//ELEMENTS CARTE (DECOR)//

	//frontiere//

	vector<string> frontiere = {

		"ffffffff",
		"f______f",
		"f______f",
		"f______f",
		"f______f",
		"f______f",
		"f______f",
		"f______f",
		"ffffffff",
	};


	//affichage de frontiere dans la console//
	for (size_t i = 0; i < frontiere.size(); i++)
	{
		string slt = frontiere[i];
		for (size_t t = 0; t < frontiere[0].size(); t++)
		{
			cout << slt[t];
		}
		cout << endl;
	}

	//lave//
	vector<string> riviereLave = {

		"________",
		"________",
		"________",
		"________",
		"______f_",
		"__ff____",
		"________",
		"________",
		"________",
	};


	//affichage de lave dans la console//
	for (size_t i = 0; i < riviereLave.size(); i++)
	{
		string slt = riviereLave[i];
		for (size_t t = 0; t < riviereLave[0].size(); t++)
		{
			cout << slt[t];
		}
		cout << endl;
	}

	//FIN ELEMENTS CARTE (DECOR)//

#pragma region interface
#pragma region pt vie et compteur brique


	sf::Font font;
	if (!font.loadFromFile("BebasNeue-Regular.ttf"))
	{
		// erreur...
	}


	sf::Text interfaceVie;
	sf::Text interfaceBrique;
	// choix de la police � utiliser
	interfaceVie.setFont(font); // font est un sf::Font
	interfaceBrique.setFont(font);
	// choix de la taille des caract�res
	interfaceVie.setCharacterSize(30); // exprim�e en pixels, pas en points !
	interfaceBrique.setCharacterSize(30);
	// choix de la couleur du texte
	interfaceVie.setFillColor(sf::Color::Blue);
	interfaceBrique.setFillColor(sf::Color::Blue);
	// choix du style du texte
	interfaceVie.setStyle(sf::Text::Bold);
	interfaceBrique.setStyle(sf::Text::Bold);
	interfaceVie.setPosition(10.0f, 0.0f);
	interfaceBrique.setPosition(300.0f, 0.0f);
#pragma endregion
#pragma endregion

#pragma region player
	if (!playerTexture.loadFromFile("trump_run.png"))
	{
		cout << "Texture error" << endl;
	}
	Player player_trump(playerTexture);
	player_trump._Sprite.setPosition(400, 450);
#pragma endregion

	///////////////////////// VECTOR ///////////////////////// 
	///////////////////////// COLLECTABLES ///////////////////

	if (!tacosTexture.loadFromFile("tacos.png"))
	{
		cout << "Texture error" << endl;
	}
	Collectable tacos(tacosTexture);
	vector <sf::Sprite> tacosTab;
	for (size_t i = 0; i < 5; i++)
	{
		sf::Sprite tacos;
		tacos.setTexture(tacosTexture);
		int tile_x;
		int tile_y;
		do {
			tile_x = rand() % 8;
			tile_y = rand() % 9;
			//cout << "tentative rat�e";
		} while (frontiere[tile_y][tile_x] == 'f');
		tacos.setPosition(tile_x * 100, tile_y * 100);

		tacos.setScale(0.5, 0.5);
		tacosTab.push_back(tacos);
	}

	if (!briqueTexture.loadFromFile("brique.png"))
	{
		cout << "Texture error" << endl;
	}
	Collectable brique(briqueTexture);
	vector <sf::Sprite> briqueTab;
	for (size_t i = 0; i < 15; i++)
	{
		sf::Sprite brique;
		brique.setTexture(briqueTexture);
		int tile_x;
		int tile_y;
		do {
			tile_x = rand() % 8;
			tile_y = rand() % 9;
		} while (frontiere[tile_y][tile_x] == 'f');
		brique.setPosition(tile_x * 100, tile_y * 100);

		brique.setScale(0.5, 0.5);
		briqueTab.push_back(brique);
	}
	///////////////////////// FIN COLLECTABLES ///////////////////
	///////////////////////// ENNEMIS ///////////////////////////

	if (!pinataTexture.loadFromFile("pinata.png"))
	{
		cout << "Texture error" << endl;
	}
	Ennemis pinata(pinataTexture);
	vector <Ennemis> pinataTab;
	for (size_t i = 0; i < 2; i++)
	{
		Ennemis pinata;
		pinata._Sprite.setTexture(pinataTexture);
		int tile_x;
		int tile_y;
		do {
			tile_x = rand() % 8;
			tile_y = rand() % 9;
			//cout << "tentative rat�e";
		} while (frontiere[tile_y][tile_x] == 'f');
		pinata._Sprite.setPosition(tile_x * 100, tile_y * 100);

		pinata._Sprite.setScale(1.0, 1.0);
		pinataTab.push_back(pinata);
	}


	if (!mexicanTexture.loadFromFile("mexican.png"))
	{
		cout << "Texture error" << endl;
	}
	Ennemis mexican(mexicanTexture);
	vector <Ennemis> mexicanTab;
	for (size_t i = 0; i < 2; i++)
	{
		Ennemis mexican;
		mexican._Sprite.setTexture(mexicanTexture);
		int tile_x;
		int tile_y;
		do {
			tile_x = rand() % 8;
			tile_y = rand() % 9;
			//cout << "tentative rat�e";
		} while (frontiere[tile_y][tile_x] == 'f');
		mexican._Sprite.setPosition(tile_x * 100, tile_y * 100);

		mexican._Sprite.setScale(1.0, 1.0);
		mexicanTab.push_back(mexican);
	}

	///////////////////////// FIN ENNEMIS ////////////////////////

	///////////////////////// BOX ////////////////////////////////
	if (!boxTexture.loadFromFile("box.png"))
	{
		cout << "Texture error" << endl;
	}
	box box(boxTexture);
	vector <sf::Sprite> boxTab;
	for (size_t i = 0; i < 2; i++)
	{
		sf::Sprite box;
		box.setTexture(boxTexture);
		int tile_x;
		int tile_y;
		do {
			tile_x = rand() % 8;
			tile_y = rand() % 9;
			//cout << "tentative rat�e";
		} while (frontiere[tile_y][tile_x] == 'f');
		box.setPosition(tile_x * 100, tile_y * 100);

		//box.setScale(1.0, 1.0);
		boxTab.push_back(box);
	}
	/////////////////////////FIN BOX /////////////////////////////
	///////////////////////// FIN VECTOR ///////////////////////// 

	while (window.isOpen())
	{
		///////////////////////// SFML EVENTS ////////////////////////////////////////////////////////////////////////////
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		///////////////////////// FIN SFML EVENTS ///////////////////
		///////////////////////// KEYPRESS ///////////////////////// //////////////////////////////////////
		horizontal = 0;
		vertical = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player_trump.moveLeft(horizontal);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player_trump.moveRight(horizontal);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player_trump.moveUp(vertical);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player_trump.moveDown(vertical);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{

			if (player_trump.tweetTime)
			{
				Projectile project(player_trump._Sprite.getPosition().x, player_trump._Sprite.getPosition().y, player_trump.direction_H, player_trump.direction_V);
				project.sprite.setTexture(t_projectile);
				projectiles.push_back(project);
				player_trump.shootTweet();
			}
		}

		///////////////////////// FIN KEYPRESS ///////////////////////// 
		///////////////////////// UPDATE /////////////////////////

		interfaceVie.setString("Point de Vie : " + to_string(player_trump.ptVie));
		interfaceBrique.setString("Briques : " + to_string(briquesCount));
		playerCenter = sf::Vector2f(player_trump._Sprite.getPosition().x, player_trump._Sprite.getPosition().y);


		// Projectile Vs pinata
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			projectiles[i].update();
			for (size_t y = 0; y < pinataTab.size(); y++)
			{


				if (pinataTab[y].ennemisHaveTakeDamage == false)
				{
					if (Collision::BoundingBoxTest(projectiles[i].sprite, pinataTab[y]._Sprite))
					{

						pinataTab[y].ennemisTakeDamage(100);

						if (pinataTab[y].ptVieEnnemis <= 0)
						{
							//pinataTab.erase(pinataTab.begin() + y);
							pinataTab[y]._Sprite.setTexture(pinata_brokenTexture);
						}
						projectiles.erase(projectiles.begin() + i);
						continue;
					}
				}
			}
		}


		// Projectile Vs mexican
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			for (size_t y = 0; y < mexicanTab.size(); y++)
			{


				if (mexicanTab[y].ennemisHaveTakeDamage == false)
				{
					if (Collision::BoundingBoxTest(projectiles[i].sprite, mexicanTab[y]._Sprite))
					{

						mexicanTab[y].ennemisTakeDamage(1);

						if (mexicanTab[y].ptVieEnnemis <= 0)
						{
							//mexicanTab.erase(mexicanTab.begin() + y);
							mexicanTab[y]._Sprite.setTexture(hatTexture);

							mexicanTab[y].isMort = true;

						}
						projectiles.erase(projectiles.begin() + i);
					}
				}
			}
		}

		// Projectile Vs bord de l'ecran

		for (size_t i = 0; i < projectiles.size(); i++)
		{
			if ((projectiles[i].sprite.getPosition().x < 0 || projectiles[i].sprite.getPosition().x > 900) ||
				(projectiles[i].sprite.getPosition().y < 0 || projectiles[i].sprite.getPosition().y > 800))
			{
				projectiles.erase(projectiles.begin() + i);
			}
		}

		///////////////////////// FIN UPDATE /////////////////////
		///////////////////////// RENDER ///////////////////////// 
		/// Background ///
		window.draw(sol);

		for (size_t i = 0; i < frontiere.size(); i++)
		{
			string slt = frontiere[i];
			for (size_t t = 0; t < frontiere[0].size(); t++)
			{
				if (slt[t] == 'f') {
					cactus.setPosition(t * CaseTaille, i * CaseTaille);
					window.draw(cactus);
				}
			}
		}

		for (size_t i = 0; i < riviereLave.size(); i++)
		{
			string slt = riviereLave[i];
			for (size_t t = 0; t < riviereLave[0].size(); t++)
			{
				if (slt[t] == 'f') {
					lave.setPosition(t * CaseTaille, i * CaseTaille);
					window.draw(lave);
				}
			}
		}
		/// Player item etc... ///

		for (size_t i = 0; i < briqueTab.size(); i++)
		{
			window.draw(briqueTab[i]);
			if (Collision::BoundingBoxTest(player_trump._Sprite, briqueTab[i])) {
				briqueTab.erase(briqueTab.begin() + i);
				briquesCount++;
			}


		}

		for (size_t i = 0; i < tacosTab.size(); i++)
		{
			window.draw(tacosTab[i]);
			if (Collision::BoundingBoxTest(player_trump._Sprite, tacosTab[i])) {
				tacosTab.erase(tacosTab.begin() + i);
				player_trump.ptVie++;
			}
		}

		for (size_t i = 0; i < boxTab.size(); i++)
		{
			window.draw(boxTab[i]);

		}
		///////////////////////// ENNEMIS //////////////////////
		for (size_t i = 0; i < pinataTab.size(); i++)
		{
			//if (pinataTab[i].isMort == false && mexicanTab[i].isMort == false)
			window.draw(pinataTab[i]._Sprite);
			if (player_trump.invincible == false)
			{
				if (pinataTab[i].isMort == false)
				{
					if (Collision::BoundingBoxTest(player_trump._Sprite, pinataTab[i]._Sprite)) {
						player_trump.takeDamage(1);
					}
				}
				
			}
		}



		for (size_t i = 0; i < mexicanTab.size(); i++)
		{
			window.draw(mexicanTab[i]._Sprite);
			if (player_trump.invincible == false)
			{
				if (mexicanTab[i].isMort == false)
				{
					if (Collision::BoundingBoxTest(player_trump._Sprite, mexicanTab[i]._Sprite)) {
						  player_trump.takeDamage(1);
					}
				}
			}
		}

		player_trump.update();
		///////////////////////// FIN ENNEMIS //////////////////////

		window.draw(player_trump._Sprite);


		for (size_t i = 0; i < projectiles.size(); i++)
		{
			window.draw(projectiles[i].sprite);
		}


		/// interface ///

		window.draw(interfaceVie);
		window.draw(interfaceBrique);

		///////////////////////// FIN RENDER //////////////////////
		window.display();

	}
}
