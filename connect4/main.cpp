#include <iostream>
#include <SFML/Graphics.hpp>
#include "Connect4.h"
#include "Menu.h"
#include "Game.h"

int main()
{
    Game* game = new Game();
    game->display();

    return 0;
}