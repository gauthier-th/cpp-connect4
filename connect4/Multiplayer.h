#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Config.h"
#include "Button.h"
#include "Game.h"

#include "json.hpp"

#include "WebSocket.h"
#include <boost/beast/core.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>

using nlohmann::json;

class Multiplayer
{
private:
	sf::Font font;
	std::vector<Button*> buttons;
	std::vector<sf::Text> texts;
	Config config;
	std::shared_ptr<WebSocket> ws;
	sf::RenderWindow* window;
	json serversList = nullptr;
	bool gameCreated = false;
	std::string gameId;
	std::string userId;
	bool youStart;
	bool startGameWindow = false;
	Game* game;
	void websocket();
	void updateList();
	void display();
public:
	Multiplayer(Config _config);
	void start();
	void createGame(std::string gameId, std::string userId);
	void joinGame(std::string userId, bool youStart);
	void startGame(bool youStart);
};