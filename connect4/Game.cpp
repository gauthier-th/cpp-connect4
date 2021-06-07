#include <iostream>
#include "Game.h"
#include "Button.h"

Game::Game(GameType _gameType): gameType(_gameType)
{
}
Game::Game(GameType _gameType, std::shared_ptr<WebSocket> _ws, std::string _userId, bool _youStart): gameType(_gameType), ws(_ws), userId(_userId), youStart(_youStart)
{
}

void Game::display()
{
	this->window = new sf::RenderWindow(sf::VideoMode(735, 630), "Connect 4", sf::Style::None + sf::Style::Titlebar + sf::Style::Close);
    if (this->gameType == GameType::MULTIPLAYER)
    {
        this->connect4 = new Connect4(this->youStart);
        this->grid = new Grid(this->window, this->connect4, !this->youStart);
    }
    else
    {
        this->connect4 = new Connect4();
        this->grid = new Grid(this->window, this->connect4);
    }

    while (this->window->isOpen())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window->close();
            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*this->window);
                this->grid->hover(localPosition, this->endType);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*this->window);
                if (this->grid->quit(localPosition, this->endType) && this->endType != 0)
                    this->window->close();
                else if ((this->gameType == GameType::MULTIPLAYER && this->connect4->getPlayer() == 1) || (this->gameType != GameType::MULTIPLAYER && endType == 0))
                {
                    int col = this->grid->clickedColumnlocalPosition(localPosition);
                    if (col >= 0 && col < Connect4::SIZE_X && !this->connect4->columnFilled(col))
                    {
                        this->ws->placeToken(this->userId, col);
                        this->placeToken(col);
                    }
                }
            }
        }

        this->window->clear();
        this->grid->draw();
        if (this->endType != 0) {
            if (this->gameType == GameType::LOCAL) {
                if (this->endType == 1)
                    this->grid->displayMessage("Player 1 won!", sf::Color(0x002AE0FF));
                else if (this->endType == 2)
                    this->grid->displayMessage("Player 2 won!", sf::Color(0x002AE0FF));
                else
                    this->grid->displayMessage("Equality!\nThe grid is full.", sf::Color(0x002AE0FF));
            }
            else {
                if (this->endType == 1)
                    this->grid->displayMessage("You won!", sf::Color(0x002AE0FF));
                else if (this->endType == 2)
                    this->grid->displayMessage("You lost!", sf::Color(0x002AE0FF));
                else
                    this->grid->displayMessage("Equality!\nThe grid is full.", sf::Color(0x002AE0FF));
            }
        }
        this->window->display();
    }
}

void Game::placeToken(int col)
{
    if (col >= 0 && col < Connect4::SIZE_X && !this->connect4->columnFilled(col))
    {
        bool win = this->connect4->addToken(col);

        if (win) {
            endType = this->connect4->getPlayer();
            this->grid->hideHover();
        }
        else if (this->connect4->gridFilled()) {
            endType = 3;
            this->grid->hideHover();
        }

        this->connect4->next();
    }
}

void Game::tokenEvent(int column)
{
    this->placeToken(column);
}