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
	int etat = 0;
	Carte carte;
	const int CaseTaille = 100;

	bool invincible;

	int horizontal = 0;
	int vertical = 0;

	
	int ancien_horizontal = -1;
	int ancien_vertical = 0;

	float speed = 0;


	sf::Vector2f playerCenter;
	vector<Projectile> projectiles;
	sf::Sprite pinata_broken;

	//Définir dimensions fenêtre et musique)

	sf::RenderWindow window(sf::VideoMode(800, 900), "SFML works!");
	window.setKeyRepeatEnabled(false);
	sf::Music music;
	sf::Clock clockInvincible;
	sf::Clock clockKeyPress;

	sf::RectangleShape cactus(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape sol(sf::Vector2f(800.0f, 900.0f));
	sf::RectangleShape lave(sf::Vector2f(100.0f, 100.0f));

	//Sprites
	sf::Sprite chest;
	sf::Sprite key;
	sf::Sprite door_open;
	sf::Sprite door_close;
	sf::Sprite caisseDansLave;
	sf::Sprite menu;
	sf::Sprite gameOverEcran;
	sf::Sprite screenEnd;
	sf::Sprite bouton_start;
	sf::Sprite bouton_credits;
	sf::Sprite bouton_quitter;
	sf::Sprite bouton_restart;

	//Définir textures 

	//décor
	sf::Texture solTexture;
	sf::Texture cactusTexture;
	sf::Texture laveTexture;
	sf::Texture caisseDansLaveTexture;
	sf::Texture chestOpenTexture;
	sf::Texture chestCloseTexture;
	sf::Texture doorOpenTexture;
	sf::Texture doorCloseTexture;

	//joueur
	sf::Texture playerTexture;
	sf::Texture t_projectile;
	sf::Texture attackTexture;
	sf::Texture dieTexture;

	//collectable
	sf::Texture tacosTexture;
	sf::Texture briqueTexture;
	sf::Texture keyTexture;

	//ennemis vaincus
	sf::Texture hatTexture;
	sf::Texture pinata_brokenTexture;

	//écrans
	sf::Texture menuTexture;
	sf::Texture screenEndTexture;
	sf::Texture gameOverEcranTexture;

	//boutons
	sf::Texture bouton_startTexture;
	sf::Texture bouton_creditsTexture;
	sf::Texture bouton_restartTexture;
	sf::Texture bouton_quitterTexture;

	//Rechercher textures dans doc

	//texture décor 
	solTexture.loadFromFile("sable.jpg");
	cactusTexture.loadFromFile("cactus.png");
	laveTexture.loadFromFile("lave.jpg");
	caisseDansLaveTexture.loadFromFile("chemin_lave.png");

	//projectile trump
	t_projectile.loadFromFile("twitter.png");

	//texture ennemis vaincus
	pinata_brokenTexture.loadFromFile("broken-pinata.png");
	hatTexture.loadFromFile("mexican_hat.png");

	//sprites texture trump
	attackTexture.loadFromFile("trump_attack.png");
	//stuntTexture.loadFromFile("trump_stunt.png");
	dieTexture.loadFromFile("dying_trump.png");

	//coffre texture
	chestOpenTexture.loadFromFile("chest_open.png");
	chestCloseTexture.loadFromFile("chest_close.png");

	//clés texture dans coffre
	keyTexture.loadFromFile("hamburger.png");
	key.setTexture(keyTexture);

	//porte texture
	doorOpenTexture.loadFromFile("door_open.png");
	doorCloseTexture.loadFromFile("door_close.png");

	//écrans
	menuTexture.loadFromFile("menu.jpg");
	screenEndTexture.loadFromFile("end.jpg");
	gameOverEcranTexture.loadFromFile("gameover.jpg");

	//boutons
	bouton_creditsTexture.loadFromFile("button_credits.png");
	bouton_quitterTexture.loadFromFile("button_quitter.png");
	bouton_startTexture.loadFromFile("button_start.png");
	bouton_restartTexture.loadFromFile("button_restart.png");

	//SONS//

	//SoundBuffer

	sf::SoundBuffer eatSoundBuffer;
	sf::SoundBuffer shootTweetSoundBuffer;
	sf::SoundBuffer keySoundBuffer;
	//::SoundBuffer eatSoundBuffer;
	sf::SoundBuffer gameOverSoundBuffer;
	sf::SoundBuffer deathPinataSoundBuffer;
	sf::SoundBuffer deathMexicanSoundBuffer;
	sf::SoundBuffer takeDamageSoundBuffer;

	//LOAD SONS

	if (!eatSoundBuffer.loadFromFile("eat.ogg"))
	{
	}
	if (!shootTweetSoundBuffer.loadFromFile("shootTweet.ogg"))
	{
	}
	if (!keySoundBuffer.loadFromFile("key.ogg"))
	{
	}
	if (!gameOverSoundBuffer.loadFromFile("gameOver.ogg"))
	{
	}
	if (!deathPinataSoundBuffer.loadFromFile("deathPinata.ogg"))
	{
	}
	if (!deathMexicanSoundBuffer.loadFromFile("deathMexican.ogg"))
	{
	}
	if (!takeDamageSoundBuffer.loadFromFile("takeDamage.ogg"))
	{
	}

	//Sound

	sf::Sound soundEat;
	sf::Sound soundshootTweet;
	sf::Sound soundKey;
	sf::Sound soundGameOver;
	sf::Sound soundPinata;
	sf::Sound soundMexican;
	sf::Sound soundTakeDamage;

	//Sounds assignés

	soundEat.setBuffer(eatSoundBuffer);
	soundshootTweet.setBuffer(shootTweetSoundBuffer);
	soundKey.setBuffer(keySoundBuffer);
	soundGameOver.setBuffer(gameOverSoundBuffer);
	soundPinata.setBuffer(deathPinataSoundBuffer);
	soundMexican.setBuffer(deathMexicanSoundBuffer);
	soundTakeDamage.setBuffer(takeDamageSoundBuffer);

	//MUSIC//

	if (!music.openFromFile("Jarabes.ogg"))
	{

	}
	music.play();
	music.setVolume(7.f);
	music.setLoop(true);

	//FIN MUSIC//

	//Appliquer Textures

	cactus.setTexture(&cactusTexture);
	sol.setTexture(&solTexture);
	lave.setTexture(&laveTexture);
	door_open.setTexture(doorOpenTexture);
	door_close.setTexture(doorCloseTexture);
	caisseDansLave.setTexture(caisseDansLaveTexture);
	menu.setTexture(menuTexture);
	gameOverEcran.setTexture(gameOverEcranTexture);
	screenEnd.setTexture(screenEndTexture);
	bouton_credits.setTexture(bouton_creditsTexture);
	bouton_quitter.setTexture(bouton_quitterTexture);
	bouton_restart.setTexture(bouton_restartTexture);
	bouton_start.setTexture(bouton_startTexture);

#pragma region interface
#pragma region pt vie et compteur brique


	sf::Font font;
	if (!font.loadFromFile("BebasNeue-Regular.ttf"))
	{
		// erreur...
	}


	sf::Text interfaceVie;
	sf::Text interfaceBrique;
	sf::Text interfaceTweet;
	// choix de la police à utiliser
	interfaceVie.setFont(font); // font est un sf::Font
	interfaceBrique.setFont(font);
	interfaceTweet.setFont(font);
	// choix de la taille des caractères
	interfaceVie.setCharacterSize(30); // exprimée en pixels, pas en points !
	interfaceBrique.setCharacterSize(30);
	interfaceTweet.setCharacterSize(30);
	// choix de la couleur du texte
	interfaceVie.setFillColor(sf::Color::Blue);
	interfaceBrique.setFillColor(sf::Color::Blue);
	interfaceTweet.setFillColor(sf::Color::Blue);
	// choix du style du texte
	interfaceVie.setStyle(sf::Text::Bold);
	interfaceBrique.setStyle(sf::Text::Bold);
	interfaceTweet.setStyle(sf::Text::Bold);
	interfaceVie.setPosition(10.0f, 0.0f);
	interfaceBrique.setPosition(300.0f, 0.0f);
	interfaceTweet.setPosition(500.0f, 0.0f);

#pragma endregion
#pragma endregion

#pragma region player
	if (!playerTexture.loadFromFile("happy_trump.png"))
	{
		cout << "Texture error" << endl;
	}
	Player player_trump(playerTexture);
	player_trump._Sprite.setPosition(400, 450);
	//speed = 80.f;
	player_trump.setSpeed(1);
#pragma endregion

#pragma region menu
	int selection = 0;
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

		switch (etat)
		{
		case 0:
		default:
#pragma region menu
			///////////////////////// KEYPRESS ///////////////////////////////////////////////////////////////
			if (clockKeyPress.getElapsedTime().asSeconds() > .25f)
			{

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					clockKeyPress.restart();
					selection--;
					if (selection < 0) {
						selection = 1;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					clockKeyPress.restart();

					selection++;
					if (selection > 1) {
						selection = 0;
					}
				}


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					clockKeyPress.restart();

					if (selection == 0) {
						etat = 1;
						cout << "bouton_start" << endl;

					}
					else if (selection == 1) {
						cout << "bouton_credits" << endl;
					}
				}
			}
			///////////////////////// UPDATE ///////////////////////////////////////////////////////////////
			///////////////////////// DRAW ///////////////////////////////////////////////////////////////
			window.draw(menu);

			bouton_credits.setOrigin(bouton_credits.getGlobalBounds().width / 2, bouton_credits.getGlobalBounds().height / 2);
			bouton_start.setOrigin(bouton_start.getGlobalBounds().width / 2, bouton_start.getGlobalBounds().height / 2);

			bouton_start.setPosition(window.getSize().x / 3, window.getSize().y / 6 * 5);
			bouton_credits.setPosition(window.getSize().x / 3 * 2, window.getSize().y / 6 * 5);
			if (selection == 0) {
				brique.setPosition(window.getSize().x / 3 - bouton_credits.getGlobalBounds().width / 2, window.getSize().y / 6 * 5);
			}
			else {
				brique.setPosition(window.getSize().x / 3 * 2 - bouton_credits.getGlobalBounds().width / 2, window.getSize().y / 6 * 5);
			}
			window.draw(bouton_credits);
			bouton_credits.setScale(0.8f, 0.8f);
			//window.draw(bouton_restart);
			window.draw(bouton_start);
			bouton_start.setScale(0.8f, 0.8f);
			window.draw(brique);

			//window.draw(bouton_quitter);
#pragma endregion
			break;
		case 1: // jeu
#pragma region jeu



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

			//TIR

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{

				if (player_trump.tweetTime)
				{
					if (carte.niveaux[carte.niveau_actuel].tweetCount > 0) {
						Projectile project(player_trump._Sprite.getPosition().x, player_trump._Sprite.getPosition().y, ancien_horizontal, ancien_vertical);
						project.sprite.setTexture(t_projectile);
						projectiles.push_back(project);
						player_trump.shootTweet();
						player_trump._Sprite.setTexture(attackTexture);
						player_trump.spriteReturn = true;
						soundshootTweet.play();
						carte.niveaux[carte.niveau_actuel].tweetCount--;
						cout << carte.niveaux[carte.niveau_actuel].tweetCount << endl;
					}
				}

			}


			horizontal = 0;
			vertical = 0;

			//DEPLACEMENTS JOUEUR

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
			if (carte.niveaux[carte.niveau_actuel].briquesCount == 3)
			{
				coffreOuvert = true;
				chest.setTexture(chestOpenTexture);
				soundKey.play();



			}
			else if (carte.niveaux[carte.niveau_actuel].briquesCount < 3)
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
					player_trump.move(horizontal , vertical );
				}
				int xx = player_trump._Sprite.getPosition().x / 100;
				int yy = player_trump._Sprite.getPosition().y / 100;
				case_actuelle = carte.niveaux[carte.niveau_actuel].decor[xx][yy];

				//tacos
				if (case_actuelle == "t")
				{
					player_trump.ptVie++;
					carte.niveaux[carte.niveau_actuel].decor[xx][yy] = "_";

					soundEat.play();
				}
				//brique
				else if (case_actuelle == "b")
				{
					carte.niveaux[carte.niveau_actuel].briquesCount++;
					carte.niveaux[carte.niveau_actuel].decor[xx][yy] = "_";
				}
				//hamburger
				else if (case_actuelle == "h")
				{
					//window.draw(door_open),
					carte.niveaux[carte.niveau_actuel].haveKey = true;
					soundEat.play();


					//carte.niveaux[carte.niveau_actuel].decor[xx][yy] = "_";
				}
				else if (case_actuelle == "d")
				{
					//if (carte.niveau_actuel < carte.niveaux.size()) {
					carte.niveau_actuel = 1;
					//}
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

					carte.niveaux[carte.niveau_actuel].decor[xx][yy] = "q";
					carte.niveaux[carte.niveau_actuel].boxx.erase(carte.niveaux[carte.niveau_actuel].boxx.begin() + i);
					//caisseDansLave.setTexture(caisseDansLaveTexture);
					//caisseDansLave.getPosition().x / 100;
					//caisseDansLave.getPosition().y / 100;
				}
			}
			//sprite attack
			if (player_trump.spriteReturn)
			{
				if (player_trump._ClockReturnSprite.getElapsedTime().asSeconds() > 1)
				{
					player_trump.spriteAttackFinish();
					player_trump._Sprite.setTexture(playerTexture);

				}
			}
			// écran game over
			if (player_trump.gameOver == true)
			{
				player_trump._Sprite.setTexture(dieTexture);

				if (player_trump.screenGameOver == false)
				{
					player_trump.screenGameOver = true;
					player_trump.ClockDeath.restart();
					soundGameOver.play();

				}
				else {

					player_trump.screenGameOver = true;
					if (player_trump.ClockDeath.getElapsedTime().asSeconds() >= 1)
					{

						music.stop();
					}
				}
				//cout << "T'as PERDU !!!" << endl;

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
							soundPinata.play();

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
							soundMexican.play();

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
			interfaceBrique.setString("Briques : " + to_string(carte.niveaux[carte.niveau_actuel].briquesCount) + "/3");
			interfaceTweet.setString("Tweets : " + to_string(carte.niveaux[carte.niveau_actuel].tweetCount) + "/20");

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
					else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "q") {
						caisseDansLave.setPosition(x * CaseTaille, y * CaseTaille);
						window.draw(caisseDansLave);
					}
					else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "h") {
						chest.setPosition(x * CaseTaille, y * CaseTaille);
						key.setPosition(x * CaseTaille, y * CaseTaille);
						window.draw(chest);
						if (carte.niveaux[carte.niveau_actuel].briquesCount >= 3) {

							if (carte.niveaux[carte.niveau_actuel].haveKey == false) {
								window.draw(key);

							}
						}

					}
					else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "d") {
						if (carte.niveaux[carte.niveau_actuel].haveKey == true)
						{
							door_open.setPosition(x * CaseTaille, y * CaseTaille);
							window.draw(door_open);

						}
						else
						{
							door_close.setPosition(x * CaseTaille, y * CaseTaille);
							window.draw(door_close);
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
		//Pinatas
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
							soundTakeDamage.play();
						}
					}

				}
			}


			//Mexicains
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
							soundTakeDamage.play();

						}
					}
				}
			}
#pragma endregion



			player_trump.update();
			///////////////////////// FIN ENNEMIS //////////////////////

			//affichage des hitboxs et des sprites du joueur
			//window.draw(player_trump.ghost);
			window.draw(player_trump._Sprite);
			//window.draw(player_trump.satouch);

			for (size_t i = 0; i < projectiles.size(); i++)
			{
				window.draw(projectiles[i].sprite);

			}


			/// interface ///

			window.draw(interfaceVie);
			window.draw(interfaceBrique);
			window.draw(interfaceTweet);

			if (player_trump.gameOver == true) {

				window.draw(gameOverEcran);

			}
			///////////////////////// FIN RENDER //////////////////////


#pragma endregion
			break;
		}
		window.display();

	}
}
