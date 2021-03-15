#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Connect4.h"
#include "Grid.h"

class Game
{
private:
	sf::RenderWindow* window;
	Connect4* connect4;
	Grid* grid;
public:
	Game();
	void display();
};