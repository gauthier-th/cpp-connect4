#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Connect4.h"
#include "Grid.h"
#include "GameType.h"

class Game
{
private:
	sf::RenderWindow* window;
	Connect4* connect4;
	Grid* grid;
	GameType gameType;
public:
	Game(GameType _gameType);
	void display();
};