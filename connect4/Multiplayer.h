#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Config.h"
#include "Button.h"

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
	json serversList = nullptr;
	void websocket();
	void upadteList();
public:
	Multiplayer(Config _config);
	void display();
	void createGame();
	void joinGame(std::string id, std::string username);
};