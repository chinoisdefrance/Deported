#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;

class Player 
{

private:
	sf::Vector2i _Source;//Declare Source (Sprite Sheet Crop)
	enum _Direction { Down, Left, Right, Up }; //Declare Direction Enumeration

	//ANIMATION DATA
	float _Speed; //Player Speed
	sf::Clock _AnimClock; //Player Animation Clock
	sf::Time _AnimTime; //Player Animation Time
	sf::Texture stuntTexture;

public:
	sf::Sprite _Sprite;//Declare Player Sprite
	sf::Clock _ClockInvincible;
	sf::Clock _ClockReturnSprite;
	sf::Clock tweetClock;
	Player(sf::Texture&);//Overload Constructor
	//~Player(); //Destructor

	//PLAYER MOVEMENT FUNCTIONS
	void moveUp(int);
	void moveDown(int);
	void moveRight(int);
	void moveLeft(int);
	void setSpeed(float, sf::Time);


	int direction_H;
	int direction_V;

	//Player Sprite et height/width
	int imageSize = 100;

	sf::Sprite getSprite() const;

	sf::Sprite getPosition();

	//Character stuff

	
	int ptVie = 5;
	int y;
	int x;
	bool invincible = false;
	bool tweetTime = false;
	bool spriteReturn = false;
	bool haveTakeDamage = false;


	sf::Clock ClockDeath;
	bool gameOver = false;
	bool screenGameOver = false;

	void player_move(int, int);
	void shootTweet();
	void spriteAttackFinish();
	void takeDamage(int damage);
	void update();
};

