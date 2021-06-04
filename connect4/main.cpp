#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "WebSocket.h"

#include <boost/beast/core.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>

int main()
{
    Menu menu = Menu();
    menu.afficher();

    return 0;
}