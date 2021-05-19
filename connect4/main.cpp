#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "WebSocket.h"

int main()
{
    //Menu menu = Menu();
    //menu.afficher();
    WebSocket websocket = WebSocket();
    websocket.test();

    return 0;
}