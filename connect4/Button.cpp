#include "Button.h"

void Button::updateProperties()
{
	this->rectangleShape->setFillColor(this->backgroundColor);
	this->rectangleShape->setPosition(this->position);
	this->rectangleShape->setSize(this->size);
	this->textShape->setString(this->textContent);
	this->textShape->setFont(this->font);
	this->textShape->setFillColor(this->textColor);
	this->textShape->setCharacterSize(24);
}

Button::Button(sf::Font _font, std::string _textContent, sf::Color _backgroundColor, sf::Vector2f _position, sf::Vector2f _size, sf::Color _textColor)
{
	this->textContent = _textContent;
	this->backgroundColor = _backgroundColor;
	this->font = _font;
	this->position = _position;
	this->size = _size;
	this->textColor = _textColor;
	this->rectangleShape = new sf::RectangleShape(this->size);
	this->textShape = new sf::Text();
	this->updateProperties();
}
Button::Button(sf::Font _font, std::string _textContent)
{
	this->font = _font;
	this->textContent = _textContent;
	this->rectangleShape = new sf::RectangleShape(this->size);
	this->textShape = new sf::Text();
	this->updateProperties();
}
Button::Button(sf::Font _font)
{
	this->font = _font;
	this->rectangleShape = new sf::RectangleShape(this->size);
	this->textShape = new sf::Text();
	this->updateProperties();
}

void Button::setTextContent(std::string _textContent)
{
	this->textContent = _textContent;
	this->updateProperties();
}
void Button::setBackgroundColor(sf::Color _backgroundColor)
{
	this->backgroundColor = _backgroundColor;
	this->updateProperties();
}
void Button::setTextColor(sf::Color _textColor)
{
	this->textColor = _textColor;
	this->updateProperties();
}
void Button::setFont(sf::Font _font)
{
	this->font = _font;
	this->updateProperties();
}
void Button::setSize(sf::Vector2f _size)
{
	this->size = _size;
	this->updateProperties();
}
void Button::setPosition(sf::Vector2f _position)
{
	this->position = _position;
	this->updateProperties();
}

sf::RectangleShape* Button::getRectangleShape()
{
	return this->rectangleShape;
}
sf::Text* Button::gettextShape()
{
	return this->textShape;
}

void Button::draw(sf::RenderWindow* window)
{
	sf::FloatRect textRect = this->textShape->getLocalBounds();
	this->textShape->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	this->textShape->setPosition(sf::Vector2f(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2));
	window->draw(*this->rectangleShape);
	window->draw(*this->textShape);
}