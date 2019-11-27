#include "Player.h"

//caractéristique du joueur

Player::Player(sf::Texture& TEMP_Trump)
{
	_Sprite.setTexture(TEMP_Trump);

	if (!stuntTexture.loadFromFile("images/trump_stunt.png"))
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

//sprite du joueur

sf::Sprite Player::getSprite() const
{

	return sf::Sprite();
}

sf::Sprite Player::getPosition()
{
	return sf::Sprite();
}

// mouvements du joueur

void Player::player_move(int move_x, int move_y)
{
	move_x = 0;
	move_y = 0;
}

// pour tirer

void Player::shootTweet()
{
	tweetClock.restart();
	tweetTime = false;
}

//changer le sprite du joueur quand il attaque

void Player::spriteAttackFinish()
{
	_ClockReturnSprite.restart();
	spriteReturn = false;
}

//quand le joueur prend des dégâts le sprite change et quand il n'a plus de points de vie, un écran de game over apparaît

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

//update du joueur (temps d'invicibilité)

void Player::update()
{
	if (haveTakeDamage == true) {

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

//hitboxs du joueur

void Player::inputs(int hori, int verti)
{
	satouch.setPosition(_Sprite.getPosition().x, _Sprite.getPosition().y);
	ghost.setPosition(satouch.getPosition().x + hori, satouch.getPosition().y + verti);
}


//vitesse du sprite calqué sur la vitesse du joueur

void Player::move(float xx, float yy)
{

	_Sprite.move(_Speed * xx, _Speed * yy);
}

//vitesse joueur

void Player::setSpeed(float _Speed)
{
	this->_Speed = _Speed;
	
}
