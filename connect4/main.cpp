#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "WebSocket.h"
#include <string>

#include <boost/beast/core.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>
#include "json.hpp"

using nlohmann::json;

int main()
{
    Menu menu = Menu();
    menu.afficher();

    /*net::io_context ioc;

    // Launch the asynchronous operation
    std::shared_ptr<WebSocket> ws = std::make_shared<WebSocket>(ioc);
    ws->setReadCallback([](std::string message) {
        std::cout << message << std::endl;
    });
    ws->connect("localhost", "3000");

    // Run the I/O service. The call will return when
    // the socket is closed.
    ioc.run();*/

    return 0;
}