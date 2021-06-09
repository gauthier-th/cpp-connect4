#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Connect4.h"
#include "Grid.h"
#include "GameType.h"
#include "WebSocket.h"

class Game
{
private:
	sf::RenderWindow* window;
	Connect4* connect4;
	Grid* grid;
	GameType gameType;
	std::shared_ptr<WebSocket> ws;
	std::string userId;
	int endType = 0;
	void placeToken(int col);
	bool youStart;
public:
	Game(GameType _gameType);
	Game(GameType _gameType, std::shared_ptr<WebSocket> _ws, std::string _userId, bool youStart);
	void display();
	void tokenEvent(int col);
	void end();
};