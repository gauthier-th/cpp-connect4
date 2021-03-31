#pragma once
#include <SFML/Graphics.hpp>
#include "Connect4.h"
#include "Button.h"

class Grid
{
private:
	sf::RenderWindow* window;
	Connect4* connect4;
	sf::Texture textureGrid;
	sf::Texture textureRedToken;
	sf::Texture textureYellowToken;
	sf::Font font;
	int hoverColumn = -1;
	Button* quitButton;
public:
	Grid(sf::RenderWindow* window, Connect4* connect4);
	void draw();
	void hover(sf::Vector2i localPosition, int endType);
	void hideHover();
	int clickedColumnlocalPosition(sf::Vector2i localPosition);
	void displayMessage(std::string message, sf::Color color);
	sf::Font getFont();
	bool quit(sf::Vector2i localPosition, int endType);
};