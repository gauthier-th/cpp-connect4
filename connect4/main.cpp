#include <iostream>
#include <SFML/Graphics.hpp>
#include "Connect4.h"
#include "Menu.h"
#include "Game.h"

int main()
{
    /*Game* game = new Game();
    game->display();*/

    Menu menu = Menu();
    menu.afficher();

    return 0;
}