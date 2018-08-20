#pragma once
#include "SFML/Graphics.hpp"
#include <vector>


struct Tile {
public:
	Tile();

	void operator++();
	void operator++(int);
	void open();

	sf::Sprite sprite;
	bool isOpen;
	bool isBomb;
	bool isFlag;

	int type;
	
};