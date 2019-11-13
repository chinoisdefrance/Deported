#include "Player.h"

Player::Player(sf::Texture& TEMP_Trump)
{
	_Sprite.setTexture(TEMP_Trump);

	if (!stuntTexture.loadFromFile("trump_stunt.png"))
	{
		cout << "Texture error" << endl;
	}
	direction_H = 0;
	direction_V = 0;
	_Sprite.setOrigin(50, 50);


	//hitbox joueur
	satouch.setSize(sf::Vector2f(_Sprite.getGlobalBounds().width - satouchMarge, _Sprite.getGlobalBounds().height - satouchMarge));
	satouch.setOrigin(_Sprite.getOrigin().x - satouchMarge / 2, _Sprite.getOrigin().y - satouchMarge / 2);
	satouch.setFillColor(sf::Color(0, 0, 255, 128));

	//ghost joueur qui permet d'entrer en contact avec objet un peu avant que le sprite n'entre en collision avec l'objet
	ghost.setSize(satouch.getSize());
	//ghost.setOrigin(sf::Vector2f(satouch.getGlobalBounds().width / 2, satouch.getGlobalBounds().height / 2));
	ghost.setOrigin(satouch.getOrigin());
	ghost.setFillColor(sf::Color(255, 0, 0, 128));
}


sf::Sprite Player::getSprite() const
{

	return sf::Sprite();
}

sf::Sprite Player::getPosition()
{
	return sf::Sprite();
}


void Player::player_move(int move_x, int move_y)
{
	move_x = 0;
	move_y = 0;
}

void Player::shootTweet()
{
	tweetClock.restart();
	tweetTime = false;
}

void Player::spriteAttackFinish()
{
	_ClockReturnSprite.restart();
	spriteReturn = false;
}

void Player::takeDamage(int damage = 1)
{

	if (ptVie <= 0)
	{
		gameOver = true;

	}
	else
	{
		ptVie -= damage;
		_Sprite.setColor(sf::Color::Red);
		_Sprite.setTexture(stuntTexture);
		_ClockInvincible.restart();
		invincible = true;
		haveTakeDamage = true;
	}
}

void Player::update()
{
	if (haveTakeDamage == true) {

		cout << "update " << endl;
		if (_ClockInvincible.getElapsedTime().asSeconds() >= 0.5)
		{
			invincible = false;
			haveTakeDamage = false;
			_Sprite.setColor(sf::Color::White);
		}

	}
	if (tweetClock.getElapsedTime().asSeconds() >= 0.5)
	{
		tweetTime = true;
	}


}

void Player::inputs(int hori, int verti)
{
	satouch.setPosition(_Sprite.getPosition().x, _Sprite.getPosition().y);
	ghost.setPosition(satouch.getPosition().x + hori, satouch.getPosition().y + verti);
}




void Player::setSpeed(float TEMP_Speed, sf::Time TEMP_AnimTime)
{
	_Speed = TEMP_Speed;
	_AnimTime = TEMP_AnimTime;
}
