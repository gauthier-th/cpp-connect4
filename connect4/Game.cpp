#include <iostream>
#include "Game.h"

Game::Game()
{
}

void Game::display()
{
	this->window = new sf::RenderWindow(sf::VideoMode(735, 630), "Connect 4", sf::Style::None + sf::Style::Titlebar + sf::Style::Close);
	this->connect4 = new Connect4();
	this->grid = new Grid(this->window, this->connect4);

    int endType = 0;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseMoved && endType == 0)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                this->grid->hover(localPosition);
            }
            if (event.type == sf::Event::MouseButtonPressed && endType == 0)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                int col = this->grid->clickedColumnlocalPosition(localPosition);

                if (col >= 0 && col < Connect4::SIZE_X && !this->connect4->columnFilled(col))
                {
                    bool win = this->connect4->addToken(col);

                    if (win) {
                        std::cout << "Player " << this->connect4->getPlayer() << " won!" << std::endl;
                        endType = this->connect4->getPlayer();
                        this->grid->hideHover();
                    }
                    else if (this->connect4->gridFilled()) {
                        std::cout << "Equality! The grid is full. " << std::endl;
                        endType = 3;
                        this->grid->hideHover();
                    }

                    this->connect4->next();
                }
            }
        }

        window->clear();
        this->grid->draw();
        if (endType != 0) {
            if (endType == 1)
                this->grid->displayMessage("Player 1 won!", sf::Color(0x002AE0FF));
            else if (endType == 2)
                this->grid->displayMessage("Player 2 won!", sf::Color(0x002AE0FF));
            else
                this->grid->displayMessage("Equality!\nThe grid is full.", sf::Color(0x002AE0FF));
        }
        window->display();
    }
}