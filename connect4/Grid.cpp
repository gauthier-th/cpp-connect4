#include <iostream>
#include "Grid.h"

Grid::Grid(sf::RenderWindow* _window, Connect4* _connect4): window(_window), connect4(_connect4)
{
	this->load();
}
Grid::Grid(sf::RenderWindow* _window, Connect4* _connect4, bool _inverseColor): window(_window), connect4(_connect4), inverseColor(_inverseColor)
{
	this->load();
}

void Grid::load()
{
	if (!this->textureGrid.loadFromFile("resources/empty_token.png") || !this->textureYellowToken.loadFromFile("resources/yellow_token.png") || !this->textureRedToken.loadFromFile("resources/red_token.png"))
	{
		std::cout << "Unable to load texture file" << std::endl;
	}

	if (!this->font.loadFromFile("resources/Lato-Regular.ttf"))
	{
		std::cout << "Unable to load font file" << std::endl;
	}

	this->quitButton = new Button(this->font, "Back");
}

void Grid::draw()
{
	sf::Sprite backSprite;
	backSprite.setTexture(this->textureGrid);
	sf::Sprite yellowSprite;
	yellowSprite.setTexture(this->textureYellowToken);
	sf::Sprite redSprite;
	redSprite.setTexture(this->textureRedToken);

	if (this->hoverColumn >= 0 && this->hoverColumn < Connect4::SIZE_X && !this->connect4->columnFilled(this->hoverColumn))
	{
		sf::Sprite sprite;
		if (this->connect4->getPlayer() == (inverseColor ? 2 : 1))
			sprite.setTexture(this->textureYellowToken);
		else
			sprite.setTexture(this->textureRedToken);
		sprite.setColor(sf::Color(255, 255, 255, 128));
		sprite.setPosition(sf::Vector2f(105 * this->hoverColumn, 0));
		this->window->draw(sprite);
	}

	for (int i = 0; i < Connect4::SIZE_X; i++)
	{
		for (int j = 0; j < Connect4::SIZE_Y; j++)
		{
			if (this->connect4->getGrid()[i][j] == (inverseColor ? 2 : 1))
			{
				yellowSprite.setPosition(sf::Vector2f(105 * i, 105 * (Connect4::SIZE_Y - 1 - j)));
				this->window->draw(yellowSprite);
			}
			else if (this->connect4->getGrid()[i][j] == (inverseColor ? 1 : 2))
			{
				redSprite.setPosition(sf::Vector2f(105 * i, 105 * (Connect4::SIZE_Y - 1 - j)));
				this->window->draw(redSprite);
			}

			backSprite.setPosition(sf::Vector2f(105 * i, 105 * (Connect4::SIZE_Y - 1 - j)));
			this->window->draw(backSprite);
		}
	}
}

void Grid::hover(sf::Vector2i localPosition, int endType)
{
	if (endType == 0) {
		int col = (localPosition.x - localPosition.x % 105) / 105;
		this->hoverColumn = col;
	}
	else
		this->quitButton->hover(localPosition);
}
void Grid::hideHover()
{
	this->hoverColumn = -1;
}

int Grid::clickedColumnlocalPosition(sf::Vector2i localPosition)
{
	int col = (localPosition.x - localPosition.x % 105) / 105;
	return col;
}


void Grid::displayMessage(std::string message, sf::Color color)
{
	int posX = 105 * 2;
	int posY = 105 * 2.5;

	sf::Text* textShape = new sf::Text();
	sf::RectangleShape* rectangleShape = new sf::RectangleShape();

	textShape->setPosition(sf::Vector2f(posX + (105 * 3) / 2, posY));
	textShape->setString(message);
	textShape->setFont(this->font);
	textShape->setCharacterSize(50);

	sf::FloatRect textRect = textShape->getLocalBounds();
	textShape->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	rectangleShape->setFillColor(color);
	rectangleShape->setPosition(sf::Vector2f(105 * 1, 105 * 2));
	rectangleShape->setSize(sf::Vector2f(105 * 5, 105 * 2));

	this->quitButton->setPosition(sf::Vector2f(posX + 105 / 2, posY + 105 / 2 + 10));

	this->window->draw(*rectangleShape);
	this->window->draw(*textShape);
	this->quitButton->draw(this->window);
}

bool Grid::quit(sf::Vector2i localPosition, int endType)
{
	return this->quitButton->hover(localPosition) && endType != 0;
}