#pragma once
static const int size = 10;
#include "SFML\Graphics.hpp"
#include "StateBase.h"
#include "../Objects/Tile.h"
#include <string>

class StatePlaying : public StateBase {

public:
	StatePlaying(Game& game);
	~StatePlaying();

	void handleInput();
	void update(float deltaTime);
	void draw();
	void handle_event(sf::Event& e);
private:
	void Open(int i, int j);
	std::vector<std::pair<int,int>> get_surround(int i, int j);


	Tile m_tiles[size][size];
	sf::Texture m_tileset;
	sf::Vector2f offset;

	sf::Font font;
	sf::Text bomb_count;
	sf::Text time;
	sf::Text won;

	bool lose;
	float timer;
	int m_bomb_count = 10;
	int bomb_game_count = m_bomb_count;
};