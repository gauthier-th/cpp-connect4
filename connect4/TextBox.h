#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextBox
{
private:
	bool isHover = false;
	bool isActive = false;
	sf::RectangleShape* rectangleShape;
	sf::Text* textShape;
	std::string textContent = "";
	sf::Color defaultBackgroundColor = sf::Color(0xDDDDDDFF);
	sf::Color hoverBackgroundColor = sf::Color(0xBBBBBBFF);
	sf::Color textColor = sf::Color::Black;
	sf::Font font;
	sf::Vector2f size = sf::Vector2f(210.f, 50.f);
	sf::Vector2f position = sf::Vector2f(0.f, 0.f);
	sf::Cursor defaultCursor;
	sf::Cursor textCursor;
	void updateProperties();
public:
	TextBox(sf::Font _font);
	void draw(sf::RenderWindow* window);
	bool hover(sf::Vector2i localPosition, sf::RenderWindow* window);
	void focus();
	void blur();
	void text(sf::String _text);
	void setTextContent(std::string _textContent);
	void setDefaultBackgroundColor(sf::Color _backgroundColor);
	void setHoverBackgroundColor(sf::Color _backgroundColor);
	void setTextColor(sf::Color _textColor);
	void setFont(sf::Font _font);
	void setSize(sf::Vector2f _size);
	void setPosition(sf::Vector2f _position);
};