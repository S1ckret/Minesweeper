#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "SFML\Graphics.hpp"
#include "State\StateBase.h"
#include "State\StatePlaying.h"

class Game {
public:
	Game();

	void run();
	void pop_state();
	template <typename T, typename... Args>
	void push_state(Args&&... args);

	std::vector<std::unique_ptr<StateBase>> states;
	sf::RenderWindow window;
private:
	void try_pop();
	void handle_event();
	StateBase& get_current_state();

private:
	sf::Clock game_clock;
	float delta;

	bool should_pop;
};

template <typename T, typename... Args>
void Game::push_state(Args&&... args) {
	states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}

