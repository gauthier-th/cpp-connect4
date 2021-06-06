#include <iostream>
#include <vector>
#include "Multiplayer.h"
#include "Game.h"
#include <thread>
#include <functional>

Multiplayer::Multiplayer(Config _config): config(_config)
{
    std::thread t1(&Multiplayer::websocket, this);
    std::thread t2(&Multiplayer::display, this);
    t1.join();
    t2.join();
}

void Multiplayer::websocket()
{
    net::io_context ioc;

    // Launch the asynchronous operation
    this->ws = std::make_shared<WebSocket>(ioc);
    this->ws->setReadCallback([&](json payload) {
        if (payload["type"] == "list") {
            this->serversList = payload["games"];
            this->upadteList();
        }
    });
    //auto qsd = std::bind(&Multiplayer::connected, this);
    this->ws->connect("localhost", "3000", [&]() {
        this->ws->listGames();
    });

    // Run the I/O service. The call will return when
    // the socket is closed.
    ioc.run();
}

void Multiplayer::upadteList()
{
    if (this->serversList != nullptr)
    {
        int size = 0;

        for (int i = 0; i < this->serversList.size(); i++)
        {
            std::string id = this->serversList[i]["id"];
            std::string username = this->serversList[i]["username"];

            sf::Text server;
            server.setString(username);
            server.setFont(this->font);
            server.setCharacterSize(20);
            server.setPosition(50, 100 + size);

            this->texts.push_back(server);

            Button* joinButton = new Button(this->font, "Join");
            joinButton->setDefaultBackgroundColor(sf::Color(0x52BE80FF));
            joinButton->setHoverBackgroundColor(sf::Color(0x27AE60FF));
            joinButton->setPosition(sf::Vector2f(250, 100 + size));
            joinButton->setSize(sf::Vector2f(100.f, 25.f));

            this->buttons.push_back(joinButton);

            size = size + 30;

            // add if i > 20 -> 2 columns
        }
    }
}

void Multiplayer::display()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(650, 650), "Connect 4 - Multiplayer", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

    if (!this->font.loadFromFile("resources/Lato-Regular.ttf"))
        std::cout << "Unable to load font file" << std::endl;

    sf::RectangleShape background(sf::Vector2f(650.f, 650.f));
    background.setFillColor(sf::Color(0x0089E3FF));

    sf::Text text;
    text.setString("List of all server");
    text.setFont(this->font);
    text.setCharacterSize(20);
    text.setPosition(200, 10);

    sf::Text server;
    server.setString("Server");
    server.setFont(this->font);
    server.setCharacterSize(20);
    server.setPosition(50, 100);

    Button* joinButton = new Button(this->font, "Join");
    joinButton->setDefaultBackgroundColor(sf::Color(0x52BE80FF));
    joinButton->setHoverBackgroundColor(sf::Color(0x27AE60FF));
    joinButton->setPosition(sf::Vector2f(200, 100));
    joinButton->setSize(sf::Vector2f(100.f, 25.f));

    Button* quitButton = new Button(this->font, "Back");
    quitButton->setSize(sf::Vector2f(150.f, 30.f));
    quitButton->setPosition(sf::Vector2f(650 - 150, 650 - 30));

    Button* createButton = new Button(this->font, "Create");
    createButton->setSize(sf::Vector2f(150.f, 30.f));
    createButton->setPosition(sf::Vector2f(0, 650 - 30));
    createButton->setDefaultBackgroundColor(sf::Color(0x52BE80FF));
    createButton->setHoverBackgroundColor(sf::Color(0x27AE60FF));

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                this->ws->close();
                window->close();
            }

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                quitButton->hover(localPosition);
                createButton->hover(localPosition);
                for (int i = 0; i < this->buttons.size(); i++)
                {
                    this->buttons[i]->hover(localPosition);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                if (quitButton->hover(localPosition))
                {
                    this->ws->close();
                    window->close();
                }
                if (createButton->hover(localPosition))
                    this->createGame();
                for (int i = 0; i < this->buttons.size(); i++) {
                    if (this->buttons[i]->hover(localPosition)) {
                        window->setVisible(false);
                        this->joinGame(this->serversList[i]["id"], this->config.getUsername());
                        window->setVisible(true);
                    }
                }
            }
        }

        window->clear();

        window->draw(background);

        for (int i = 0; i < this->buttons.size(); i++) {
            window->draw(this->texts[i]);
            this->buttons[i]->draw(window);
        }
        
        window->draw(text);
        quitButton->draw(window);
        createButton->draw(window);
        window->display();
    }
}

void Multiplayer::createGame()
{

}

void Multiplayer::joinGame(std::string id, std::string username)
{
    Game* game = new Game(GameType::MULTIPLAYER);
    game->display();
}