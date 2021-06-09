#pragma once
#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>
#include "Connect4.h"
#include "Button.h"
#include "GameType.h"
#include "Animation.h"

class Grid
{
private:
	sf::RenderWindow* window;
	Connect4* connect4;
	sf::Texture textureGrid;
	sf::Texture textureRedToken;
	sf::Texture textureYellowToken;
	sf::Font font;
	GameType gameType;
	void load();
	int hoverColumn = -1;
	Button* quitButton;
	sf::Sprite backSprite;
	sf::Sprite yellowSprite;
	sf::Sprite redSprite;
	bool inverseColor = false;
	std::vector<std::tuple<int, int, Animation*>> animations;
public:
	Grid(sf::RenderWindow* window, Connect4* connect4, GameType gameType);
	Grid(sf::RenderWindow* window, Connect4* connect4, GameType gameType, bool _inverseColor);
	void draw();
	void hover(sf::Vector2i localPosition, int endType);
	void hideHover();
	int clickedColumnlocalPosition(sf::Vector2i localPosition);
	void addToken(int col);
	void displayMessage(std::string message, sf::Color color);
	sf::Font getFont();
	bool quit(sf::Vector2i localPosition, int endType);
};