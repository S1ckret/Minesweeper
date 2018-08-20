#include "Game.h"



Game::Game() {
	window.create(sf::VideoMode(800, 600, 32), "test");
	window.setVerticalSyncEnabled(1);
	push_state<StatePlaying>(*this);
}

void Game::run() {
	game_clock.restart();
	while (window.isOpen() && !states.empty()) {
		float delta = game_clock.getElapsedTime().asSeconds();
		game_clock.restart();

		StateBase& current_state = get_current_state();

		current_state.update(delta);

		window.clear();
		current_state.draw();
		window.display();

		handle_event();
		try_pop();
	}
}

void Game::pop_state()
{
	should_pop = true;	
}

void Game::try_pop()
{
	if (should_pop) {
		states.pop_back();
		should_pop = false;
	}
}

void Game::handle_event()
{
	sf::Event e;
	while (window.pollEvent(e)) {

		get_current_state().handle_event(e);

		if (e.type == sf::Event::Closed) {
			window.close();
		}
	}
}

StateBase & Game::get_current_state()
{
	return *states.back();
}
