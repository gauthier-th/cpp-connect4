#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape* rectangleShape;
	sf::Text* textShape;
	std::string textContent;
	sf::Color backgroundColor = sf::Color(0xFF341AFF);
	sf::Color textColor = sf::Color::Black;
	sf::Font font;
	sf::Vector2f size = sf::Vector2f(210.f, 50.f);
	sf::Vector2f position = sf::Vector2f(0.f, 0.f);
	void updateProperties();
public:
	Button(sf::Font _font);
	Button(sf::Font _font, std::string _textContent);
	Button(sf::Font _font, std::string _textContent, sf::Color _backgroundColor, sf::Vector2f _position, sf::Vector2f _size, sf::Color _textColor);
	void setTextContent(std::string _textContent);
	void setBackgroundColor(sf::Color _backgroundColor);
	void setTextColor(sf::Color _textColor);
	void setFont(sf::Font _font);
	void setSize(sf::Vector2f _size);
	void setPosition(sf::Vector2f _position);
	sf::RectangleShape* getRectangleShape();
	sf::Text* gettextShape();
	void draw(sf::RenderWindow* window);
};