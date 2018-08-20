#include "Tile.h"

Tile::Tile() {
	isOpen = false;
	isFlag = false;
	isBomb = false;
	type = 0;

}

void Tile::open()
{
	isOpen = true;
	sprite.setTextureRect(sf::IntRect(type * 32, 0, 32, 32));
}

void Tile::operator++()
{
	if (type != 9) {
		type++;
	}
}


void Tile::operator++(int)
{
	if (type != 9) {
		type++;
	}
}
