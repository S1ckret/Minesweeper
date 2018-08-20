#pragma once

#include "SFML\Graphics.hpp"

class Game;

class StateBase {
public:
	StateBase(Game& game) : m_game_ptr(&game) { }
	virtual ~StateBase() = default;

	virtual void handleInput() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void handle_event(sf::Event& e) = 0;
protected:
	Game* m_game_ptr;
};