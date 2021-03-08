#include <iostream>
#include <SFML/Graphics.hpp>
#include "Connect4.h"
#include "Menu.h"

int main()
{
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/

    /*Connect4* p4 = new Connect4();

    while (true) {
        system("cls");
        p4->showGrid();
        std::cout << "It's player " << p4->getPlayer() << "'s turn!" << std::endl;
        int colonne = 0;
        while (colonne < 1 || colonne > Connect4::SIZE_X) {
            std::cout << "Enter a column number between 1 and 7: ";
            std::cin >> colonne;
            if (colonne <= Connect4::SIZE_X && p4->columnFilled(colonne - 1)) {
                std::cout << "This column has already been completed!" << std::endl;
                colonne = 0;
            }
        }
        bool victoire = p4->addToken(colonne - 1);
        if (victoire) {
            system("cls");
            p4->showGrid();
            std::cout << "Player " << p4->getPlayer() << " won!" << std::endl;
            break;
        }
        else if (p4->gridFilled()) {
            system("cls");
            p4->showGrid();
            std::cout << "Equality! The grid is full. " << std::endl;
            break;
        }
        p4->next();
    }*/

    Menu* menu = new Menu();
    menu->afficher();

    return 0;
}