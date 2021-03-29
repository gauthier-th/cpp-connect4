#include <iostream>
#include <chrono>
#include "TextBox.h"
#include "Button.h"

TextBox::TextBox(sf::Font _font)
{
	this->font = _font;
	this->rectangleShape = new sf::RectangleShape(this->size);
	this->cursorShape = new sf::RectangleShape();
	this->textShape = new sf::Text();

	if (!this->defaultCursor.loadFromSystem(sf::Cursor::Arrow) || !this->textCursor.loadFromSystem(sf::Cursor::Text))
		std::cout << "Unable to load cursor." << std::endl;

	this->updateProperties();
}

void TextBox::updateProperties()
{
	if (this->isHover)
		this->rectangleShape->setFillColor(this->hoverBackgroundColor);
	else
		this->rectangleShape->setFillColor(this->defaultBackgroundColor);
	this->rectangleShape->setPosition(this->position);
	this->rectangleShape->setSize(this->size);
	this->textShape->setString(this->textContent);
	this->textShape->setFont(this->font);
	this->textShape->setFillColor(this->textColor);
	this->textShape->setCharacterSize(24);
	this->cursorShape->setFillColor(this->textColor);
}

void TextBox::draw(sf::RenderWindow* window)
{
	sf::FloatRect textRect = this->textShape->getLocalBounds();
	this->textShape->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	this->textShape->setPosition(sf::Vector2f(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2));

	if (this->isHover)
		this->rectangleShape->setFillColor(this->hoverBackgroundColor);
	else
		this->rectangleShape->setFillColor(this->defaultBackgroundColor);

	if (this->isActive) {
		this->cursorShape->setSize(sf::Vector2f(2.f, this->size.y / 1.8f));
		if (this->textContent.length() == 0)
			this->cursorShape->setPosition(sf::Vector2f(this->textShape->getPosition().x + this->textShape->getLocalBounds().width / 2 + 4.f, this->position.y + 12.f));
		else
			this->cursorShape->setPosition(sf::Vector2f(this->textShape->getPosition().x + this->textShape->getLocalBounds().width / 2 + 4.f, this->position.y + 12.f));
	}

	window->draw(*this->rectangleShape);
	window->draw(*this->textShape);
	if (this->isActive) {
		const auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		if (timestamp % 1000 < 500)
			window->draw(*this->cursorShape);
	}
}

bool TextBox::hover(sf::Vector2i localPosition, sf::RenderWindow* window)
{
	if (localPosition.x >= this->position.x && localPosition.x <= this->position.x + this->size.x && localPosition.y >= this->position.y && localPosition.y <= this->position.y + this->size.y) 
	{
		this->isHover = true;
		window->setMouseCursor(this->textCursor);
	}
	else
	{
		this->isHover = false;
		window->setMouseCursor(this->defaultCursor);
	}
	return this->isHover;
}

void TextBox::focus()
{
	this->isActive = true;
	this->rectangleShape->setOutlineThickness(2.f);
	this->rectangleShape->setOutlineColor(sf::Color(0, 0, 0));
}

void TextBox::blur()
{
	this->isActive = false;
	this->rectangleShape->setOutlineThickness(0.f);
}

void TextBox::text(sf::String _text)
{
	std::string result = "";
	std::string from = _text.toAnsiString();
	for (int i = 0; i < from.length(); i++) {
		if (from[i] > 31 && from[i] != 127)
			result += from[i];
	}
	if (this->isActive) {
		if (_text.toAnsiString().length() > 0 && _text.toAnsiString()[0] == 8 && this->textContent.length() > 0)
			this->setTextContent(this->textContent.substr(0, this->textContent.length() - 1));
		else
			this->setTextContent(this->textContent + result);
	}
}

void TextBox::setTextContent(std::string _textContent)
{
	this->textContent = _textContent;
	this->updateProperties();
}
void TextBox::setDefaultBackgroundColor(sf::Color _defaultBackgroundColor)
{
	this->defaultBackgroundColor = _defaultBackgroundColor;
	this->updateProperties();
}
void TextBox::setHoverBackgroundColor(sf::Color _hoverBackgroundColor)
{
	this->hoverBackgroundColor = _hoverBackgroundColor;
	this->updateProperties();
}
void TextBox::setTextColor(sf::Color _textColor)
{
	this->textColor = _textColor;
	this->updateProperties();
}
void TextBox::setFont(sf::Font _font)
{
	this->font = _font;
	this->updateProperties();
}
void TextBox::setSize(sf::Vector2f _size)
{
	this->size = _size;
	this->updateProperties();
}
void TextBox::setPosition(sf::Vector2f _position)
{
	this->position = _position;
	this->updateProperties();
}