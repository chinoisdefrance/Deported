#include "Player.h"




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


Player::Player(sf::Texture& TEMP_Trump)
{
	_Sprite.setTexture(TEMP_Trump);

	if (!stuntTexture.loadFromFile("trump_stunt.png"))
	{
		cout << "Texture error" << endl;
	}
	direction_H = 0;
	direction_V = 0;
	//_Sprite.setPosition(400 - imageSize, 450 - imageSize);
	//_Sprite.setPosition(0, 0);
	//_Sprite.setScale(1.0f, 1.0f);
	//sf::Vector2i _Source(1, Down);
	//_Sprite.setTextureRect(sf::IntRect(_Source.x * imageSize, _Source.y * imageSize, imageSize, imageSize));

	//_AnimTime = sf::milliseconds(80);
	//_Speed = 0.20;
	_Sprite.setOrigin(_Sprite.getGlobalBounds().width / 2, _Sprite.getGlobalBounds().height / 2);
}

void Player::moveUp(int vertical)
{
	_Source.y = Up;
	direction_V = -1;
	direction_H = 0;


	if (_AnimClock.getElapsedTime() > _AnimTime)
	{
		_Sprite.setTextureRect(sf::IntRect(_Source.x * imageSize, 2 * imageSize, imageSize, imageSize));
	}

	_Source.x++;
	if (_Source.x * imageSize >= _Sprite.getTexture()->getSize().x)
	{
		_Source.x = 0;
	}
	if (_Sprite.getPosition().y > 0)
	{
		_Sprite.move(0, -_Speed);
	}


	_AnimClock.restart();
}

void Player::moveDown(int vertical)
{
	_Source.y = Down;
	direction_V = 1;
	direction_H = 0;


	if (_AnimClock.getElapsedTime() > _AnimTime)
	{
		_Sprite.setTextureRect(sf::IntRect(_Source.x * imageSize, 0, imageSize, imageSize));
	}

	_Source.x++;
	if (_Source.x * imageSize >= _Sprite.getTexture()->getSize().x)
	{
		_Source.x = 0;
	}
	if (_Sprite.getPosition().y < 900)
	{
		_Sprite.move(0, _Speed);
	}

	_AnimClock.restart();
}

void Player::moveRight(int horizontal)
{
	direction_H = 1;
	direction_V = 0;

	_Source.y = Right;
	_Sprite.move(_Speed, 0);

	if (_AnimClock.getElapsedTime() > _AnimTime)
	{
		_Sprite.setTextureRect(sf::IntRect(_Source.x * imageSize, 1 * imageSize, imageSize, imageSize));
	}

	_Source.x++;
	if (_Source.x * imageSize >= _Sprite.getTexture()->getSize().x)
	{
		_Source.x = 0;
	}
	if (_Sprite.getPosition().x < 800)
	{
		horizontal = 1;
	}

	_AnimClock.restart();
}

void Player::moveLeft(int horizontal)
{

	direction_H = -1;
	direction_V = 0;

	_Source.y = Left;
	_Sprite.move(-_Speed, 0);

	if (_AnimClock.getElapsedTime() > _AnimTime)
	{
		_Sprite.setTextureRect(sf::IntRect(_Source.x * imageSize, 3 * imageSize, imageSize, imageSize));
	}

	_Source.x++;
	if (_Source.x * imageSize >= _Sprite.getTexture()->getSize().x)
	{
		_Source.x = 0;
	}
	if (_Sprite.getPosition().x < 800)
	{
		horizontal = -1;
	}

	_AnimClock.restart();
}


void Player::setSpeed(float TEMP_Speed, sf::Time TEMP_AnimTime)
{
	_Speed = TEMP_Speed;
	_AnimTime = TEMP_AnimTime;
}
