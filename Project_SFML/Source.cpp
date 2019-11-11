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

	Carte carte;
	const int CaseTaille = 100;

	int briquesCount = 0;
	bool invincible;

	int horizontal = 0;
	int vertical = 0;


	int ancien_horizontal = -1;
	int ancien_vertical = 0;
	bool haveKey = false;



	sf::Vector2f playerCenter;
	vector<Projectile> projectiles;
	sf::Sprite pinata_broken;

	//Définir dimensions fenêtre et musique)

	sf::RenderWindow window(sf::VideoMode(800, 900), "SFML works!");
	window.setKeyRepeatEnabled(false);
	sf::Music music;
	sf::Clock clockInvincible;

	sf::RectangleShape cactus(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape sol(sf::Vector2f(800.0f, 900.0f));
	sf::RectangleShape lave(sf::Vector2f(100.0f, 100.0f));

	sf::Sprite gameOverEcran;
	sf::Sprite chest;
	sf::Sprite key;
	sf::Sprite door;

	//Définir textures 

	sf::Texture playerTexture;
	sf::Texture briqueTexture;

	sf::Texture cactusTexture;
	sf::Texture solTexture;
	sf::Texture tacosTexture;

	//ennemis vaincus
	sf::Texture hatTexture;
	sf::Texture pinata_brokenTexture;
	//fin ennemis vaincus
	sf::Texture laveTexture;
	sf::Texture t_projectile;
	sf::Texture attackTexture;

	sf::Texture dieTexture;
	sf::Texture ecranGameOver;
	sf::Texture screenEnd;
	sf::Texture gameOverEcranTexture;
	sf::Texture chestOpenTexture;
	sf::Texture chestCloseTexture;
	sf::Texture keyTexture;
	sf::Texture doorTexture;


	//Rechercher textures dans doc

	solTexture.loadFromFile("sable.jpg");
	cactusTexture.loadFromFile("cactus.png");
	laveTexture.loadFromFile("lave.jpg");
	t_projectile.loadFromFile("twitter.png");
	pinata_brokenTexture.loadFromFile("broken-pinata.png");
	hatTexture.loadFromFile("mexican_hat.png");
	attackTexture.loadFromFile("trump_attack.png");
	//stuntTexture.loadFromFile("trump_stunt.png");
	dieTexture.loadFromFile("dying_trump.png");
	ecranGameOver.loadFromFile("gameOver.png");
	screenEnd.loadFromFile("end.jpg");

	gameOverEcranTexture.loadFromFile("gameOver.png");
	chestOpenTexture.loadFromFile("chest_open.png");
	chestCloseTexture.loadFromFile("chest_close.png");
	keyTexture.loadFromFile("hamburger.png");
	key.setTexture(keyTexture);
	key.setScale(.8, .8);
	gameOverEcran.setTexture(gameOverEcranTexture);
	doorTexture.loadFromFile("door.png");

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
	door.setTexture(doorTexture);







#pragma region interface
#pragma region pt vie et compteur brique


	sf::Font font;
	if (!font.loadFromFile("BebasNeue-Regular.ttf"))
	{
		// erreur...
	}


	sf::Text interfaceVie;
	sf::Text interfaceBrique;
	// choix de la police à utiliser
	interfaceVie.setFont(font); // font est un sf::Font
	interfaceBrique.setFont(font);
	// choix de la taille des caractères
	interfaceVie.setCharacterSize(30); // exprimée en pixels, pas en points !
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
	if (!playerTexture.loadFromFile("happy_trump.png"))
	{
		cout << "Texture error" << endl;
	}
	Player player_trump(playerTexture);
	player_trump._Sprite.setPosition(400, 450);
#pragma endregion

	///////////////////////// VECTOR ///////////////////////// 
	///////////////////////// COLLECTABLES ///////////////////

	if (!tacosTexture.loadFromFile("tacotrump.png"))
	{
		cout << "Texture error" << endl;
	}

	sf::Sprite tacos;
	tacos.setTexture(tacosTexture);
	if (!briqueTexture.loadFromFile("brique.png"))
	{
		cout << "Texture error" << endl;
	}

	sf::Sprite brique;
	brique.setTexture(briqueTexture);
	///////////////////////// FIN COLLECTABLES ///////////////////



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



		if (horizontal == 0 && vertical == 0)
		{

		}
		else
		{
			ancien_horizontal = horizontal;
			ancien_vertical = vertical;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{

			if (player_trump.tweetTime)
			{
				Projectile project(player_trump._Sprite.getPosition().x, player_trump._Sprite.getPosition().y, ancien_horizontal, ancien_vertical);
				project.sprite.setTexture(t_projectile);
				projectiles.push_back(project);
				player_trump.shootTweet();
				player_trump._Sprite.setTexture(attackTexture);
				player_trump.spriteReturn = true;
			}

		}


		horizontal = 0;
		vertical = 0;

		if (player_trump.gameOver == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				horizontal = -1;
				player_trump._Sprite.setScale(1, 1);
				//player_trump.moveLeft(horizontal);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				horizontal = 1;
				player_trump._Sprite.setScale(-1, 1);
				//player_trump.moveRight(horizontal);

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				vertical = -1;
				//player_trump.moveUp(vertical);

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				vertical = 1;
				//player_trump.moveDown(vertical);

			}



			player_trump.inputs(horizontal, vertical);
		}





		///////////////////////// FIN KEYPRESS ///////////////////////// 
		///////////////////////// UPDATE /////////////////////////
		bool coffreOuvert = false;

		//coffre 
		if (briquesCount == 3)
		{
			coffreOuvert = true;
			
			chest.setTexture(chestOpenTexture);

		}
		else if (briquesCount < 3)
		{
			chest.setTexture(chestCloseTexture);
		}


		//COLLiSIONS
		string case_actuelle;
		if (!Collision::tile_place_meeting(horizontal, vertical, player_trump.satouch, carte, true, 0, true)) {

			bool boitebloquee = false;
			bool collisionBoxBetween = false;



#pragma region collisions
			for (size_t i = 0; i < carte.niveaux[carte.niveau_actuel].boxx.size(); i++)
			{
				// collision entre joeur et colis
				if (Collision::mob_place_meeting(player_trump.ghost, carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite)) {
					//verifie si la position du joueur adititioné a son deplacement touche un mur statique
					if (Collision::tile_place_meeting(horizontal, vertical, carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite, carte, false, 0, false) == false) {
						//(int xOffset, int yOffset, sf::Sprite sprite, Carte& room, bool center, int reduction, bool bloqueSol)
						for (size_t y = 0; y < carte.niveaux[carte.niveau_actuel].boxx.size(); y++)
						{
							// si la caisse poussée est en contact avec une autre caisse elle est stoppée
							if (carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite.getPosition() != carte.niveaux[carte.niveau_actuel].boxx[y]._Sprite.getPosition())
							{
								// empeche de verifier la collision d'un caisse avec elle meme
								if (Collision::mob_place_meeting(carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite, carte.niveaux[carte.niveau_actuel].boxx[y]._Sprite))
								{
									collisionBoxBetween = true;
								}
							}

						}
						if (!collisionBoxBetween)
						{
							//deplacement de la caisse
							carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite.move(horizontal, vertical);
						}
					}
					else {
						boitebloquee = true;
					}


				}
			}
#pragma endregion

			if (boitebloquee == false && collisionBoxBetween == false) {
				//deplacement du joueur
				player_trump._Sprite.move(horizontal * 0.20, vertical * 0.20);
			}
			int xx = player_trump._Sprite.getPosition().x / 100;
			int yy = player_trump._Sprite.getPosition().y / 100;
			case_actuelle = carte.niveaux[carte.niveau_actuel].decor[xx][yy];

			//tacos
			if (case_actuelle == "t")
			{
				player_trump.ptVie++;
				carte.niveaux[carte.niveau_actuel].decor[xx][yy] = "_";
			}
			//brique
			else if (case_actuelle == "b")
			{
				briquesCount++;
				carte.niveaux[carte.niveau_actuel].decor[xx][yy] = "_";
			}
			//hamburger
			else if (case_actuelle == "h")
			{
				haveKey = true;

				//carte.niveaux[carte.niveau_actuel].decor[xx][yy] = "_";
			}


		}

		//marcher sur lave grâce à caisses
		for (size_t i = 0; i < carte.niveaux[carte.niveau_actuel].boxx.size(); i++)
		{
			int xx = carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite.getPosition().x / 100;
			int yy = carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite.getPosition().y / 100;
			case_actuelle = carte.niveaux[carte.niveau_actuel].decor[xx][yy];
			if (case_actuelle == "l")
			{

				carte.niveaux[carte.niveau_actuel].decor[xx][yy] = "_";
				carte.niveaux[carte.niveau_actuel].boxx.erase(carte.niveaux[carte.niveau_actuel].boxx.begin() + i);
			}
		}

		if (player_trump.spriteReturn)
		{
			if (player_trump._ClockReturnSprite.getElapsedTime().asSeconds() > 1)
			{
				player_trump.spriteAttackFinish();
				player_trump._Sprite.setTexture(playerTexture);

			}
		}

		if (player_trump.gameOver == true)
		{
			player_trump._Sprite.setTexture(dieTexture);
		}

		if (player_trump.gameOver == true) {

			if (player_trump.screenGameOver == false)
			{
				player_trump.screenGameOver = true;
				player_trump.ClockDeath.restart();
			}
			else {

				player_trump.screenGameOver = true;
				if (player_trump.ClockDeath.getElapsedTime().asSeconds() >= 1)
				{


				}
			}
			cout << "T'as PERDU !!!" << endl;

		}
		playerCenter = sf::Vector2f(player_trump._Sprite.getPosition().x, player_trump._Sprite.getPosition().y);


		// Projectile Vs pinata
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			projectiles[i].update();
		}
		for (size_t y = 0; y < carte.niveaux[carte.niveau_actuel].Pinatas.size(); y++)
		{
			for (size_t i = 0; i < projectiles.size(); i++)
			{



				if (carte.niveaux[carte.niveau_actuel].Pinatas[y].ennemisHaveTakeDamage == false)
				{
					if (projectiles[i].sprite.getGlobalBounds().intersects(carte.niveaux[carte.niveau_actuel].Pinatas[y]._Sprite.getGlobalBounds()))
					{

						carte.niveaux[carte.niveau_actuel].Pinatas[y].ennemisTakeDamage(1);

						if (carte.niveaux[carte.niveau_actuel].Pinatas[y].ptVieEnnemis <= 0)
						{

							carte.niveaux[carte.niveau_actuel].Pinatas[y]._Sprite.setTexture(pinata_brokenTexture);
						}
						projectiles.erase(projectiles.begin() + i);
						continue;
					}
				}
			}
		}


		// Projectile Vs mexican

		for (size_t y = 0; y < carte.niveaux[carte.niveau_actuel].Mexicans.size(); y++)
		{
			for (size_t i = 0; i < projectiles.size(); i++)
			{

				if (carte.niveaux[carte.niveau_actuel].Mexicans[y].ennemisHaveTakeDamage == false)
				{
					if (projectiles[i].sprite.getGlobalBounds().intersects(carte.niveaux[carte.niveau_actuel].Mexicans[y]._Sprite.getGlobalBounds()))
					{

						carte.niveaux[carte.niveau_actuel].Mexicans[y].ennemisTakeDamage(1);

						if (carte.niveaux[carte.niveau_actuel].Mexicans[y].ptVieEnnemis <= 0)
						{

							carte.niveaux[carte.niveau_actuel].Mexicans[y]._Sprite.setTexture(hatTexture);
						}
						projectiles.erase(projectiles.begin() + i);
						continue;
					}
				}
			}
		}

		// Projectile contre bord de l'ecran

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

		interfaceVie.setString("Point de Vie : " + to_string(player_trump.ptVie));
		interfaceBrique.setString("Briques : " + to_string(briquesCount));

		/// Background ///
		window.draw(sol);

		for (size_t y = 0; y < 9; y++)
		{
			for (size_t x = 0; x < 8; x++)
			{
				if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "f") {
					cactus.setPosition(x * CaseTaille, y * CaseTaille);
					window.draw(cactus);
				}
				else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "l") {
					lave.setPosition(x * CaseTaille, y * CaseTaille);
					window.draw(lave);
				}
				else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "b") {
					brique.setPosition(x * CaseTaille, y * CaseTaille);
					window.draw(brique);
				}
				else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "t") {
					tacos.setPosition(x * CaseTaille, y * CaseTaille);
					window.draw(tacos);
				}
				else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "h") {
					chest.setPosition(x * CaseTaille, y * CaseTaille);
					key.setPosition(x * CaseTaille, y * CaseTaille);
					window.draw(chest);
					if (briquesCount >= 3) { 
						
						if (haveKey == false) {
							window.draw(key);
							
						}
					}

				}
				else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "d") {
					
					if (haveKey == true)
					{
						door.setPosition(x* CaseTaille, y* CaseTaille);
						window.draw(door);
					}
					
				}
			}
		}
		
		
		for (size_t i = 0; i < carte.niveaux[carte.niveau_actuel].boxx.size(); i++)
		{
			window.draw(carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite);

		}
		///////////////////////// ENNEMIS //////////////////////
#pragma region ennemis
		for (size_t i = 0; i < carte.niveaux[carte.niveau_actuel].Pinatas.size(); i++)
		{
			//if (carte.niveaux[carte.niveau_actuel].Pinatas[i].isMort == false && carte.niveaux[carte.niveau_actuel].Mexicans[i].isMort == false)
			window.draw(carte.niveaux[carte.niveau_actuel].Pinatas[i]._Sprite);
			if (player_trump.invincible == false)
			{
				if (carte.niveaux[carte.niveau_actuel].Pinatas[i].isMort == false)
				{
					if (player_trump.satouch.getGlobalBounds().intersects(carte.niveaux[carte.niveau_actuel].Pinatas[i]._Sprite.getGlobalBounds()))
					{
						player_trump.takeDamage(1);

					}
				}

			}
		}



		for (size_t i = 0; i < carte.niveaux[carte.niveau_actuel].Mexicans.size(); i++)
		{
			window.draw(carte.niveaux[carte.niveau_actuel].Mexicans[i]._Sprite);
			if (player_trump.invincible == false)
			{
				if (carte.niveaux[carte.niveau_actuel].Mexicans[i].isMort == false)
				{
					if (player_trump.satouch.getGlobalBounds().intersects(carte.niveaux[carte.niveau_actuel].Mexicans[i]._Sprite.getGlobalBounds()))
					{
						player_trump.takeDamage(1);

					}
				}
			}
		}
#pragma endregion



		player_trump.update();
		///////////////////////// FIN ENNEMIS //////////////////////


		window.draw(player_trump.ghost);
		window.draw(player_trump._Sprite);
		window.draw(player_trump.satouch);

		for (size_t i = 0; i < projectiles.size(); i++)
		{
			window.draw(projectiles[i].sprite);
		}


		/// interface ///

		window.draw(interfaceVie);
		window.draw(interfaceBrique);


		if (player_trump.gameOver == true) {

			window.draw(gameOverEcran);
		}
		///////////////////////// FIN RENDER //////////////////////
		window.display();

	}
}
