#include "Collision.h"

bool Collision::tile_place_meeting(int xOffset, int yOffset, sf::RectangleShape sprite, Carte& room, bool center, int reduction, bool bloqueLeSol)
{
	int x = sprite.getPosition().x + xOffset;
	int y = sprite.getPosition().y + yOffset;
	int xp = sprite.getPosition().x;
	int yp = sprite.getPosition().y;
	int xa = xp;
	int ya = yp;
	bool meeting = false;

	sprite.setPosition(x, y);

	int bbox_left = 0;
	int bbox_right = 0;
	int bbox_top = 0;
	int bbox_bottom = 0;

	if (center) {
		bbox_left = x - sprite.getGlobalBounds().width / 2;
		bbox_right = x + sprite.getGlobalBounds().width / 2 - 1;
		bbox_top = y - sprite.getGlobalBounds().width / 2;
		bbox_bottom = y + sprite.getGlobalBounds().width / 2 - 1;
	}
	else {
		bbox_left = x;
		bbox_right = x + sprite.getGlobalBounds().width - 1;
		bbox_top = y;
		bbox_bottom = y + sprite.getGlobalBounds().width - 1;
	}
	meeting = room.tilemap_get_at_pixel(sf::Vector2i(bbox_left, bbox_top), bloqueLeSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(bbox_right, bbox_top), bloqueLeSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(bbox_left, ya), bloqueLeSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(bbox_left, bbox_bottom), bloqueLeSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(bbox_right, bbox_bottom), bloqueLeSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(xa, ya),bloqueLeSol);
	sprite.setPosition(xp, yp);
	return meeting;
}

bool Collision::tile_place_meeting(int xOffset, int yOffset, sf::Sprite sprite, Carte& room, bool center, int reduction, bool bloqueSol)
{
	int x = sprite.getPosition().x + xOffset;
	int y = sprite.getPosition().y + yOffset;
	int xp = sprite.getPosition().x;
	int yp = sprite.getPosition().y;
	int xa = xp;
	int ya = yp;
	bool meeting = false;

	sprite.setPosition(x, y);

	int bbox_left = 0;
	int bbox_right = 0;
	int bbox_top = 0;
	int bbox_bottom = 0;

	if (center) {
		bbox_left = x - sprite.getGlobalBounds().width / 2;
		bbox_right = x + sprite.getGlobalBounds().width / 2 - 1;
		bbox_top = y - sprite.getGlobalBounds().width / 2;
		bbox_bottom = y + sprite.getGlobalBounds().width / 2 - 1;
	}
	else {
		bbox_left = x;
		bbox_right = x + sprite.getGlobalBounds().width - 1;
		bbox_top = y;
		bbox_bottom = y + sprite.getGlobalBounds().width - 1;
	}
	meeting = room.tilemap_get_at_pixel(sf::Vector2i(bbox_left, bbox_top), bloqueSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(bbox_right, bbox_top), bloqueSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(bbox_left, ya), bloqueSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(bbox_left, bbox_bottom), bloqueSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(bbox_right, bbox_bottom), bloqueSol) ||
		room.tilemap_get_at_pixel(sf::Vector2i(xa, ya), bloqueSol);
	sprite.setPosition(xp, yp);
	return meeting;
}

bool Collision::mob_place_meeting(sf::Sprite moving, sf::Sprite fix, int hori, int verti)
{
	bool result = false;
	moving.move(hori, verti);
	result = moving.getGlobalBounds().intersects(fix.getGlobalBounds());
	return result;
}

bool Collision::mob_place_meeting(sf::RectangleShape moving, sf::Sprite fix, int hori, int verti)
{
	bool result = false;
	moving.move(hori, verti);
	result = moving.getGlobalBounds().intersects(fix.getGlobalBounds());
	return result;
}