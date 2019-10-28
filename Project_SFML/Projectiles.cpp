#include "Projectiles.h"

Projectile::Projectile()
{
}

Projectile::Projectile(int x, int y, int hori, int verti)
{
	direction = sf::Vector2f(hori, verti);
	sprite.setScale(0.5f, 0.5f);
	sprite.setPosition(x, y);
}

void Projectile::update()
{

	sprite.move(direction);

}
