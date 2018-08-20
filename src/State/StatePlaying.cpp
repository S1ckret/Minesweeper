#include "StatePlaying.h"
#include "../Game.h"	

StatePlaying::StatePlaying(Game & game) : StateBase(game)
{
	offset = sf::Vector2f(0.f, 100.f);
	m_tileset.loadFromFile("images/tiles.jpg");
	font.loadFromFile("images/BKANT.TTF");
	bomb_count.setFont(font);
	bomb_count.setCharacterSize(20);
	bomb_count.setFillColor(sf::Color::White);
	bomb_count.setPosition(20, 40);
	won.setFont(font);
	won.setCharacterSize(20);
	won.setFillColor(sf::Color::White);
	won.setPosition(120, 40);
	time.setFont(font);
	time.setCharacterSize(20);
	time.setFillColor(sf::Color::White);
	time.setPosition(280, 40);
	timer = 0.f;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m_tiles[i][j].sprite.setTexture(m_tileset);
			m_tiles[i][j].sprite.setTextureRect(sf::IntRect(10 * 32, 0, 32, 32));
			m_tiles[i][j].sprite.setPosition(j * 32 + offset.x, i * 32 + offset.y);
		}
	}

	int bombs = m_bomb_count;
	while (bombs > 0) {
		int i = rand() % 10;
		int j = rand() % 10;
		while (m_tiles[i][j].isBomb) {
			i = rand() % 10;
			j = rand() % 10;
		}
		m_tiles[i][j].type = 9;
		m_tiles[i][j].isBomb = true;
		bombs--;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (m_tiles[i][j].isBomb) {
				if (i - 1 > -1) {
					m_tiles[i - 1][j]++;
					if (j - 1 > -1) {
						m_tiles[i - 1][j - 1]++;
					}
					if (j + 1 < size) {
						m_tiles[i - 1][j + 1]++;
					}
				}
				if (i + 1 < size) {
					m_tiles[i + 1][j]++;
					if (j - 1 > -1) {
						m_tiles[i + 1][j - 1]++;
					}
					if (j + 1 < size) {
						m_tiles[i + 1][j + 1]++;
					}
				}
				if (j - 1 > -1) {
					m_tiles[i][j - 1]++;
				}
				if (j + 1 < size) {
					m_tiles[i][j + 1]++;
				}
			}
		}
	}


	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 10; j++) {
	//		m_tiles[i][j].open();
	//	}
	//}
}

StatePlaying::~StatePlaying()
{
}

void StatePlaying::handleInput()
{
}

void StatePlaying::update(float deltaTime)
{
	
	bomb_count.setString(std::to_string(bomb_game_count));
	if (!lose) {
		timer += deltaTime;
		time.setString(std::to_string(static_cast<int>(timer)));
	}
}

void StatePlaying::draw()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m_game_ptr->window.draw(m_tiles[i][j].sprite);
		}
	}
	m_game_ptr->window.draw(bomb_count);
	m_game_ptr->window.draw(time);
	if (lose) {
		m_game_ptr->window.draw(won);
	}
}

void StatePlaying::handle_event(sf::Event & e)
{
	if (e.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i point = sf::Mouse::getPosition(m_game_ptr->window);
		sf::Vector2f mouse_pos = m_game_ptr->window.mapPixelToCoords(point) - offset;
		mouse_pos /= 32.f;
		int i = mouse_pos.y;
		int j = mouse_pos.x;
		if (!lose) {
			if (!m_tiles[i][j].isOpen) {
				if (!m_tiles[i][j].isFlag) {
					if (e.key.code == sf::Mouse::Button::Left) {
						if (m_tiles[i][j].isBomb) {
							m_tiles[i][j].sprite.setColor(sf::Color::Red);
							won.setString("You Lose");
							lose = true;
							for (int i = 0; i < 10; i++) {
								for (int j = 0; j < 10; j++) {
									if (m_tiles[i][j].isBomb && !m_tiles[i][j].isFlag) {
										m_tiles[i][j].open();
									}
								}
							}
						}
						Open(i, j);
					}
				}
				if (e.key.code == sf::Mouse::Button::Right) {
					m_tiles[i][j].isFlag = !m_tiles[i][j].isFlag;
					if (m_tiles[i][j].isFlag) {
						m_tiles[i][j].sprite.setTextureRect(sf::IntRect(11 * 32, 0, 32, 32));
						bomb_game_count--;
						if(m_tiles[i][j].isBomb) {
							m_bomb_count--;
						}
					}
					else {
						m_tiles[i][j].sprite.setTextureRect(sf::IntRect(10 * 32, 0, 32, 32));
						bomb_game_count++;
						if (m_tiles[i][j].isBomb) {
							m_bomb_count++;
						}
					}
				}
			}

		
		
			if (m_bomb_count == 0) {
				won.setString("You Won !!!");
				lose = true;
			}
		}
	}

}

void StatePlaying::Open(int i, int j)
{
	if (!m_tiles[i][j].isOpen) {
		if (!m_tiles[i][j].isFlag) {
			m_tiles[i][j].open();
			if (m_tiles[i][j].type == 0) {
				for (std::pair<int, int> tile : get_surround(i, j)) {
					Open(tile.first, tile.second);
				}
			}
		}
	}
}

std::vector<std::pair<int, int>> StatePlaying::get_surround(int i, int j)
{
	std::vector<std::pair<int, int>> res;
	if (i - 1 > -1) {
		res.push_back(std::pair<int, int>(i - 1, j));
		
		if (j - 1 > -1) {
			res.push_back(std::pair<int, int>(i - 1, j - 1));
		}
		if (j + 1 < size) {
			res.push_back(std::pair<int, int>(i - 1, j + 1));
		}
	}
	if (i + 1 < size) {
		res.push_back(std::pair<int, int>(i + 1, j));
		if (j - 1 > -1) {
			res.push_back(std::pair<int, int>(i + 1, j - 1));
		}
		if (j + 1 < size) {
			res.push_back(std::pair<int, int>(i + 1, j + 1));
		}
	}
	if (j - 1 > -1) {
		res.push_back(std::pair<int, int>(i, j - 1));
	}
	if (j + 1 < size) {
		res.push_back(std::pair<int, int>(i, j + 1));
	}
	return res;
}

