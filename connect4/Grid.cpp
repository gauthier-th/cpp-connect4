#include "Grid.h"
#include <iostream>

Grid::Grid(sf::RenderWindow* _window, Connect4* _connect4, GameType _gameType): window(_window), connect4(_connect4), gameType(_gameType)
{
	this->load();
}
Grid::Grid(sf::RenderWindow* _window, Connect4* _connect4, GameType _gameType, bool _inverseColor): window(_window), connect4(_connect4), gameType(_gameType), inverseColor(_inverseColor)
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

	this->backSprite.setTexture(this->textureGrid);
	this->yellowSprite.setTexture(this->textureYellowToken);
	this->redSprite.setTexture(this->textureRedToken);

	this->quitButton = new Button(this->font, "Back");
}

void Grid::draw()
{
	for (int i = 0; i < this->animations.size(); i++)
	{
		auto tupleAnim = this->animations[i];
		int col = std::get<0>(tupleAnim);
		int token = std::get<1>(tupleAnim);
		int pos = std::get<2>(tupleAnim)->state();
		if (token == (this->inverseColor ? 2 : 1))
		{
			this->yellowSprite.setPosition(sf::Vector2f(105 * col, pos));
			this->window->draw(yellowSprite);
		}
		else if (token == (this->inverseColor ? 1 : 2))
		{
			this->redSprite.setPosition(sf::Vector2f(105 * col, pos));
			this->window->draw(redSprite);
		}
	}

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

	int currentAnimations[Connect4::SIZE_X];
	std::fill(currentAnimations, currentAnimations + Connect4::SIZE_X, 0);
	for (int i = 0; i < this->animations.size(); i++)
	{
		int col = std::get<0>(this->animations[i]);
		currentAnimations[col]++;
	}

	for (int i = 0; i < Connect4::SIZE_X; i++)
	{
		for (int j = Connect4::SIZE_Y - 1; j >= 0; j--)
		//for (int j = 0; j < Connect4::SIZE_Y; j++)
		{
			if (currentAnimations[i] > 0 && this->connect4->getGrid()[i][j] != 0)
				currentAnimations[i]--;
			else
			{
				if (this->connect4->getGrid()[i][j] == (this->inverseColor ? 2 : 1))
				{
					this->yellowSprite.setPosition(sf::Vector2f(105 * i, 105 * (Connect4::SIZE_Y - 1 - j)));
					this->window->draw(yellowSprite);
				}
				else if (this->connect4->getGrid()[i][j] == (this->inverseColor ? 1 : 2))
				{
					this->redSprite.setPosition(sf::Vector2f(105 * i, 105 * (Connect4::SIZE_Y - 1 - j)));
					this->window->draw(redSprite);
				}
			}

			this->backSprite.setPosition(sf::Vector2f(105 * i, 105 * (Connect4::SIZE_Y - 1 - j)));
			this->window->draw(this->backSprite);
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

void Grid::addToken(int col)
{
	int tokenCount = this->connect4->columnTokenCount(col);
	if (tokenCount < Connect4::SIZE_Y - 1)
	{
		Animation* anim = new Animation(0, 105 * (Connect4::SIZE_Y - tokenCount), 600, [&, col]() {
			for (int i = 0; i < this->animations.size(); i++)
			{
				std::cout << std::get<0>(this->animations[i]) << " : " << col << "" << std::endl;
				if (std::get<0>(this->animations[i]) == col)
				{
					std::cout << "remove token " << col << std::endl;
					this->animations.erase(this->animations.begin() + i);
					break;
				}
			}
			});
		anim->start();
		this->animations.push_back(std::make_tuple(col, this->connect4->getPlayer(), anim));
	}
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