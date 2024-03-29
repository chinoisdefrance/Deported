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
	bool havePlaySound = false;

	int horizontal = 0;
	int vertical = 0;


	int ancien_horizontal = -1;
	int ancien_vertical = 0;

	float speed = 0;


	sf::Vector2f playerCenter;
	vector<Projectile> projectiles;
	sf::Sprite pinata_broken;

	//D�finir dimensions fen�tre et musique)

	sf::RenderWindow window(sf::VideoMode(800, 900), "DEPORTED");
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
	sf::Sprite bouton_retour;
	sf::Sprite ecranCredits;

	//D�finir textures 

	//d�cor
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

	//�crans
	sf::Texture menuTexture;
	sf::Texture screenEndTexture;
	sf::Texture gameOverEcranTexture;
	sf::Texture ecranCreditsTexture;

	//boutons
	sf::Texture bouton_startTexture;
	sf::Texture bouton_creditsTexture;
	sf::Texture bouton_retourTexture;


	//Rechercher textures dans doc

	//texture d�cor 
	solTexture.loadFromFile("images/sable.jpg");
	cactusTexture.loadFromFile("images/cactus.png");
	laveTexture.loadFromFile("images/lave.jpg");
	caisseDansLaveTexture.loadFromFile("images/chemin_lave.png");

	//projectile trump
	t_projectile.loadFromFile("images/twitter.png");

	//texture ennemis vaincus
	pinata_brokenTexture.loadFromFile("images/broken-pinata.png");
	hatTexture.loadFromFile("images/mexican_hat.png");

	//sprites texture trump
	attackTexture.loadFromFile("images/trump_attack.png");
	//stuntTexture.loadFromFile("images/trump_stunt.png");
	dieTexture.loadFromFile("images/dying_trump.png");

	//coffre texture
	chestOpenTexture.loadFromFile("images/chest_open.png");
	chestCloseTexture.loadFromFile("images/chest_close.png");

	//cl�s texture dans coffre
	keyTexture.loadFromFile("images/hamburger.png");
	key.setTexture(keyTexture);

	//porte texture
	doorOpenTexture.loadFromFile("images/door_open.png");
	doorCloseTexture.loadFromFile("images/door_close.png");

	//�crans
	menuTexture.loadFromFile("images/menu.jpg");
	screenEndTexture.loadFromFile("images/end.jpg");
	gameOverEcranTexture.loadFromFile("images/gameover.jpg");
	ecranCreditsTexture.loadFromFile("images/ecran_credits.jpg");

	//boutons
	bouton_creditsTexture.loadFromFile("images/button_credits.png");
	bouton_startTexture.loadFromFile("images/button_start.png");
	bouton_retourTexture.loadFromFile("images/button_retour.png");

	//SONS//

	//SoundBuffer

	sf::SoundBuffer eatSoundBuffer;
	sf::SoundBuffer shootTweetSoundBuffer;
	sf::SoundBuffer keySoundBuffer;
	sf::SoundBuffer gameOverSoundBuffer;
	sf::SoundBuffer deathPinataSoundBuffer;
	sf::SoundBuffer deathMexicanSoundBuffer;
	sf::SoundBuffer takeDamageSoundBuffer;
	sf::SoundBuffer openChestSoundBuffer;
	sf::SoundBuffer endSoundBuffer;

	//LOAD SONS

	if (!eatSoundBuffer.loadFromFile("ogg/eat.ogg"))
	{
	}
	if (!shootTweetSoundBuffer.loadFromFile("ogg/shootTweet.ogg"))
	{
	}
	if (!keySoundBuffer.loadFromFile("ogg/key.ogg"))
	{
	}
	if (!gameOverSoundBuffer.loadFromFile("ogg/gameOver.ogg"))
	{
	}
	if (!deathPinataSoundBuffer.loadFromFile("ogg/deathPinata.ogg"))
	{
	}
	if (!deathMexicanSoundBuffer.loadFromFile("ogg/deathMexican.ogg"))
	{
	}
	if (!takeDamageSoundBuffer.loadFromFile("ogg/takeDamage.ogg"))
	{
	}
	if (!openChestSoundBuffer.loadFromFile("ogg/openChest.ogg"))
	{
	}
	if (!endSoundBuffer.loadFromFile("ogg/america.ogg"))
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
	sf::Sound soundOpenChest;
	sf::Sound soundEnd;

	//Sounds assign�s

	soundEat.setBuffer(eatSoundBuffer);
	soundshootTweet.setBuffer(shootTweetSoundBuffer);
	soundKey.setBuffer(keySoundBuffer);
	soundGameOver.setBuffer(gameOverSoundBuffer);
	soundPinata.setBuffer(deathPinataSoundBuffer);
	soundMexican.setBuffer(deathMexicanSoundBuffer);
	soundTakeDamage.setBuffer(takeDamageSoundBuffer);
	soundOpenChest.setBuffer(openChestSoundBuffer);
	soundEnd.setBuffer(endSoundBuffer);

	//MUSIC//

	if (!music.openFromFile("ogg/Jarabes.ogg"))
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
	ecranCredits.setTexture(ecranCreditsTexture);
	bouton_credits.setTexture(bouton_creditsTexture);
	bouton_retour.setTexture(bouton_retourTexture);
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
	// choix de la police � utiliser
	interfaceVie.setFont(font); // font est un sf::Font
	interfaceBrique.setFont(font);
	interfaceTweet.setFont(font);
	// choix de la taille des caract�res
	interfaceVie.setCharacterSize(30); // exprim�e en pixels, pas en points !
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
	if (!playerTexture.loadFromFile("images/happy_trump.png"))
	{
		cout << "Texture error" << endl;
	}
	Player player_trump(playerTexture);
	player_trump._Sprite.setPosition(400, 450);
	//speed = 80.f;
	player_trump.setSpeed(.6);
#pragma endregion

#pragma region menu
	int selection = 0;
#pragma endregion

	///////////////////////// VECTOR ///////////////////////// 
	///////////////////////// COLLECTABLES ///////////////////

	if (!tacosTexture.loadFromFile("images/tacotrump.png"))
	{
		cout << "Texture error" << endl;
	}

	sf::Sprite tacos;

	tacos.setTexture(tacosTexture);
	if (!briqueTexture.loadFromFile("images/brique.png"))
	{
		cout << "Texture error" << endl;
	}

	sf::Sprite brique;
	brique.setTexture(briqueTexture);
	///////////////////////// FIN COLLECTABLES ///////////////////

	///////////////////////// DEBUT DU WHILE ///////////////////

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

		//switch permettant de constuire les diff�rents menus et de naviguer entre eux

		switch (etat)
		{
		case 0:
		default:
#pragma region menu
			///////////////////////// KEYPRESS ///////////////////////////////////////////////////////////////
			if (clockKeyPress.getElapsedTime().asSeconds() > .25f)
			{
				//touches assign�es pour aller d'un bouton � l'autre
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

				//touche assign�e pour s�lectionner un choisir un bouton
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					clockKeyPress.restart();
					//deux choix possibles
					if (selection == 0) {
						etat = 1;
						cout << "bouton_start" << endl;

					}
					else if (selection == 1) {
						cout << "bouton_credits" << endl;
						etat = 2;
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
		case 2://cr�dits

			bouton_retour.setPosition(10, window.getSize().y - 160);
			bouton_retour.setScale(0.8f, 0.8f);

			if (clockKeyPress.getElapsedTime().asSeconds() > .25f)
			{

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					clockKeyPress.restart();
					etat = 0;
					selection = 0;
				}
			}
			brique.setPosition(5, window.getSize().y - 90);

			window.draw(ecranCredits);
			window.draw(bouton_retour);
			window.draw(brique);
			break;

		case 3://gameOver
			bouton_retour.setPosition(320, window.getSize().y - 120);
			bouton_retour.setScale(0.6f, 0.6f);
			
			//jouer la musique de l'�cran game over
			if (havePlaySound == false)
			{
				
				soundGameOver.play();
				havePlaySound = true;
			}
			//temps de latence quand le joueur passe d'un bouton � l'autre
			if (clockKeyPress.getElapsedTime().asSeconds() > .25f)
			{

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					clockKeyPress.restart();
					etat = 0;
					selection = 0;
				}
			}
			brique.setPosition(280, window.getSize().y - 90);
			
			//affichage de l'�cran game over, du bouton et de la brique qui montre que l'on a s�lectionn� un bouton
			window.draw(gameOverEcran);
			window.draw(bouton_retour);
			window.draw(brique);
			break;

		case 4://fin
			//musique de fin se lance et son volume est choisi ici, la musique du jeu s'arr�te
			if (havePlaySound == false)
			{
				music.stop();
				soundEnd.play();
				soundEnd.setVolume(3.f);
				havePlaySound = true;
			}
			//affichage de l'�cran de fin
			window.draw(screenEnd);
			
			//
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
			//touche d�di� au tir
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				
				if (player_trump.tweetTime)
				{
					//compteur de tweet, sprite du joueur change quand il tire, son de tire est jou�
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
			//quand le joueur n'a plus de points de vie, il ne peut plus bouger
			if (player_trump.gameOver == false)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					horizontal = -1;
					player_trump._Sprite.setScale(1, 1);
					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					horizontal = 1;
					player_trump._Sprite.setScale(-1, 1);
					

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					vertical = -1;
					

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					vertical = 1;
					

				}

				player_trump.inputs(horizontal, vertical);
			}


			///////////////////////// FIN KEYPRESS ///////////////////////// 
			///////////////////////// UPDATE /////////////////////////


			//coffre
			//si le joueur a ramass� toutes les briques, le coffre s'ouvre, le son du coffre et de la cl� sont jou�s
			if (carte.niveaux[carte.niveau_actuel].briquesCount == 3)
			{
				chest.setTexture(chestOpenTexture);
				if (carte.niveaux[carte.niveau_actuel].coffreOuvert == false) {
					soundKey.play();
					soundOpenChest.play();
				}
				carte.niveaux[carte.niveau_actuel].coffreOuvert = true;
			}
			//si le joueur n'a pas r�cup�r� toutes les briques, le coffre reste ferm�
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
						//verifie si la position du joueur aditition� a son deplacement touche un mur statique
						if (Collision::tile_place_meeting(horizontal, vertical, carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite, carte, false, 0, false) == false) {
							//(int xOffset, int yOffset, sf::Sprite sprite, Carte& room, bool center, int reduction, bool bloqueSol)
							for (size_t y = 0; y < carte.niveaux[carte.niveau_actuel].boxx.size(); y++)
							{
								// si la caisse pouss�e est en contact avec une autre caisse elle est stopp�e
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
					player_trump.move(horizontal, vertical);
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
					if (carte.niveaux[carte.niveau_actuel].coffreOuvert) {
						carte.niveaux[carte.niveau_actuel].haveKey = true;
						soundEat.play();


						//carte.niveaux[carte.niveau_actuel].decor[xx][yy] = "_";
					}
				}
				//porte
				else if (case_actuelle == "d")
				{
					//si le joueur prend la cl� il pourra changer de niveau et la porte s'ouvrira, sinon elle reste ferm�e
					if (carte.niveaux[carte.niveau_actuel].haveKey) {
						if (carte.niveau_actuel == 0)
						{
							carte.niveau_actuel = 1;
						}
						//dans le menu
						else 
						{
							etat = 4;
						}
					}
				}



			}

			//marcher sur lave gr�ce � caisses
			for (size_t i = 0; i < carte.niveaux[carte.niveau_actuel].boxx.size(); i++)
			{
				int xx = (carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite.getPosition().x + 50) / 100;
				int yy = (carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite.getPosition().y + 50) / 100;
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
			// �cran game over
			if (player_trump.gameOver == true)
			{
				//dans le menu
				etat = 3;
			}
			playerCenter = sf::Vector2f(player_trump._Sprite.getPosition().x, player_trump._Sprite.getPosition().y);


			// Projectile Vs pinata
			//tableau de vecteur de projectiles
			for (size_t i = 0; i < projectiles.size(); i++)
			{
				projectiles[i].update();
			}
			//le tableau de vecteur d'ennemis (qui les affichent sur la carte)
			for (size_t y = 0; y < carte.niveaux[carte.niveau_actuel].Pinatas.size(); y++)
			{
				for (size_t i = 0; i < projectiles.size(); i++)
				{
					//les ennemis prennent des d�g�ts quand ils sont touch�s par les projectiles du joueur
					if (carte.niveaux[carte.niveau_actuel].Pinatas[y].ennemisHaveTakeDamage == false)
					{
						if (projectiles[i].sprite.getGlobalBounds().intersects(carte.niveaux[carte.niveau_actuel].Pinatas[y]._Sprite.getGlobalBounds()))
						{
							//un son est lanc� quand les ennemis sont touch�s par les projectiles
							carte.niveaux[carte.niveau_actuel].Pinatas[y].ennemisTakeDamage(1);
							soundPinata.play();
							//les pinatas changent de sprite quand elles n'ont plus de point de vie
							if (carte.niveaux[carte.niveau_actuel].Pinatas[y].ptVieEnnemis <= 0)
							{

								carte.niveaux[carte.niveau_actuel].Pinatas[y]._Sprite.setTexture(pinata_brokenTexture);
							}
							//les projectiles disparaissent si elles touchent un ennemi
							projectiles.erase(projectiles.begin() + i);
							continue;
						}
					}
				}
			}


			// Projectile Vs mexican
			//le tableau de vecteur d'ennemis (qui les affichent sur la carte)
			for (size_t y = 0; y < carte.niveaux[carte.niveau_actuel].Mexicans.size(); y++)
			{
				for (size_t i = 0; i < projectiles.size(); i++)
				{
					//les ennemis prennent des d�g�ts quand ils sont touch�s par les projectiles du joueur
					if (carte.niveaux[carte.niveau_actuel].Mexicans[y].ennemisHaveTakeDamage == false)
					{
						//un son est lanc� quand les ennemis sont touch�s par les projectiles
						if (projectiles[i].sprite.getGlobalBounds().intersects(carte.niveaux[carte.niveau_actuel].Mexicans[y]._Sprite.getGlobalBounds()))
						{

							carte.niveaux[carte.niveau_actuel].Mexicans[y].ennemisTakeDamage(1);
							soundMexican.play();
							//les mexicains changent de sprite quand elles n'ont plus de point de vie
							if (carte.niveaux[carte.niveau_actuel].Mexicans[y].ptVieEnnemis <= 0)
							{

								carte.niveaux[carte.niveau_actuel].Mexicans[y]._Sprite.setTexture(hatTexture);
							}
							//les projectiles disparaissent si elles touchent un ennemi
							projectiles.erase(projectiles.begin() + i);
							continue;
						}
					}
				}
			}

			// Projectiles s'effacent quand ils rencontrent le bord de l'�cran

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
			//tableaux de vecteurs des cases horizontales et verticales qui composent la carte
			for (size_t y = 0; y < 9; y++)
			{
				for (size_t x = 0; x < 8; x++)
				{
					//cactus
					if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "f") {
						cactus.setPosition(x * CaseTaille, y * CaseTaille);
						window.draw(cactus);
					}
					//lave
					else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "l") {
						lave.setPosition(x * CaseTaille, y * CaseTaille);
						window.draw(lave);
					}
					//briques
					else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "b") {
						brique.setPosition(x * CaseTaille, y * CaseTaille);
						window.draw(brique);
					}
					//tacos
					else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "t") {
						tacos.setPosition(x * CaseTaille, y * CaseTaille);
						window.draw(tacos);
					}
					//caisses dans la lave
					else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "q") {
						caisseDansLave.setPosition(x * CaseTaille, y * CaseTaille);
						window.draw(caisseDansLave);
					}
					//coffre avec cl� dans le coffre
					else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "h") {
						chest.setPosition(x * CaseTaille, y * CaseTaille);
						key.setPosition(x * CaseTaille, y * CaseTaille);
						window.draw(chest);
						//afficher la cl� si le joueur a r�cup�r� toutes les briques
						if (carte.niveaux[carte.niveau_actuel].briquesCount >= 3) {

							if (carte.niveaux[carte.niveau_actuel].haveKey == false) {
								window.draw(key);

							}
						}

					}
					//porte
					else if (carte.niveaux[carte.niveau_actuel].decor[x][y] == "d") 
					{
						//porte ouverte
						if (carte.niveaux[carte.niveau_actuel].haveKey == true)
						{
							door_open.setPosition(x * CaseTaille, y * CaseTaille);
							window.draw(door_open);

						}
						//porte ferm�e
						else
						{
							door_close.setPosition(x * CaseTaille, y * CaseTaille);
							window.draw(door_close);
						}
					}
				}
			}

			//boxs
			for (size_t i = 0; i < carte.niveaux[carte.niveau_actuel].boxx.size(); i++)
			{
				window.draw(carte.niveaux[carte.niveau_actuel].boxx[i]._Sprite);

			}
			///////////////////////// ENNEMIS //////////////////////
#pragma region ennemis
		//Pinatas
			for (size_t i = 0; i < carte.niveaux[carte.niveau_actuel].Pinatas.size(); i++)
			{
				
				window.draw(carte.niveaux[carte.niveau_actuel].Pinatas[i]._Sprite);
				if (player_trump.invincible == false)
				{	
					//le joueur prend des d�g�ts s'il entre en collision avec les pinatas, un son est lanc�
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
						//le joueur prend des d�g�ts s'il entre en collision avec les mexicains, un son est lanc�
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
