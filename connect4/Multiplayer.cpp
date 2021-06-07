#include <iostream>
#include <vector>
#include "Multiplayer.h"
#include "Game.h"
#include <thread>
#include <functional>

Multiplayer::Multiplayer(Config _config): config(_config)
{
}

void Multiplayer::start()
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
        else if (payload["type"] == "create")
            this->createGame(payload["gameId"], payload["userId"]);
        else if (payload["type"] == "join") {
            this->joinGame(payload["userId"], payload["youStart"]);
            std::cout << payload.dump() << std::endl;
        }
        else
            std::cout << payload.dump() << std::endl;
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
    this->buttons.clear();
    this->texts.clear();
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
    this->window = new sf::RenderWindow(sf::VideoMode(650, 650), "Connect 4 - Multiplayer", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

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

    Button* reloadButton = new Button(this->font, "Reload");
    reloadButton->setSize(sf::Vector2f(150.f, 30.f));
    reloadButton->setPosition(sf::Vector2f(650/2 - 150/2, 650 - 30));
    reloadButton->setDefaultBackgroundColor(sf::Color(0x52BE80FF));
    reloadButton->setHoverBackgroundColor(sf::Color(0x27AE60FF));

    while (this->window->isOpen())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                this->ws->close();
                this->window->close();
            }

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*this->window);
                quitButton->hover(localPosition);
                createButton->hover(localPosition);
                reloadButton->hover(localPosition);
                for (int i = 0; i < this->buttons.size(); i++)
                {
                    this->buttons[i]->hover(localPosition);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*this->window);
                if (quitButton->hover(localPosition))
                {
                    this->ws->close();
                    this->window->close();
                }
                if (createButton->hover(localPosition) && !this->gameCreated)
                    this->ws->createGame(this->config.getUsername());
                if (reloadButton->hover(localPosition) && !this->gameCreated)
                    this->ws->listGames();
                for (int i = 0; i < this->buttons.size(); i++) {
                    if (this->buttons[i]->hover(localPosition))
                        this->ws->joinGame(this->serversList[i]["id"], this->config.getUsername());
                }
            }
        }

        this->window->clear();

        this->window->draw(background);

        for (int i = 0; i < this->buttons.size(); i++) {
            this->window->draw(this->texts[i]);
            this->buttons[i]->draw(this->window);
        }
        if (this->serversList == nullptr || this->buttons.size() == 0 || this->gameCreated)
        {
            sf::Text loading;
            if (this->serversList == nullptr)
            {
                loading.setCharacterSize(30);
                loading.setString("Loading...");
            }
            else
            {
                loading.setCharacterSize(25);
                if (this->gameCreated)
                    loading.setString("Waiting for another player...");
                else
                    loading.setString("No available room for the moment.");
            }
            loading.setFont(this->font);
            loading.setPosition(650/2 - loading.getLocalBounds().width/2, 300);
            this->window->draw(loading);
        }
        else
            this->window->draw(text);

        quitButton->draw(this->window);
        if (!this->gameCreated)
        {
            createButton->draw(this->window);
            reloadButton->draw(this->window);
        }
        this->window->display();
    }
}

void Multiplayer::createGame(std::string gameId, std::string userId)
{
    this->gameCreated = true;
    std::cout << "create game, gameId: " << gameId << " userId: " << userId << std::endl;
}

void Multiplayer::joinGame(std::string userId, bool youStart)
{
    std::cout << "join game, userId: " << userId << " youStart: " << youStart << std::endl;
    //Game* game = new Game(GameType::MULTIPLAYER);
    //game->display();
}

void Multiplayer::start(bool youStart)
{
    std::cout << "start game, youStart: " << youStart << std::endl;
}