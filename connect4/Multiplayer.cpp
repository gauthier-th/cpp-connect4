#include <iostream>
#include <vector>
#include "Multiplayer.h"
#include "Button.h"
#include "json.hpp"

using nlohmann::json;

void Multiplayer::display()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(650, 650), "Connect 4 - Multiplayer", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

    sf::Font font;
    if (!font.loadFromFile("resources/Lato-Regular.ttf"))
        std::cout << "Unable to load font file" << std::endl;

    sf::RectangleShape background(sf::Vector2f(650.f, 650.f));
    background.setFillColor(sf::Color(0x0089E3FF));

    sf::Text text;
    text.setString("List of all server");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(200, 10);

    sf::Text server;
    server.setString("Server");
    server.setFont(font);
    server.setCharacterSize(20);
    server.setPosition(50, 100);

    Button* joinButton = new Button(font, "Join");
    joinButton->setDefaultBackgroundColor(sf::Color(0x52BE80FF));
    joinButton->setHoverBackgroundColor(sf::Color(0x27AE60FF));
    joinButton->setPosition(sf::Vector2f(200, 100));
    joinButton->setSize(sf::Vector2f(100.f, 25.f));

    std::vector<Button*> buttons;
    std::vector<sf::Text> texts;

    Button* quitButton = new Button(font, "Back");
    quitButton->setSize(sf::Vector2f(150.f, 30.f));
    quitButton->setPosition(sf::Vector2f(650 - 150, 650 - 30));

    Button* createButton = new Button(font, "Create");
    createButton->setSize(sf::Vector2f(150.f, 30.f));
    createButton->setPosition(sf::Vector2f(0, 650 - 30));
    createButton->setDefaultBackgroundColor(sf::Color(0x52BE80FF));
    createButton->setHoverBackgroundColor(sf::Color(0x27AE60FF));

    json list = {
        {"type", "list" },
        {"list", json::array({
            json::object({
                {"id", "19b1ecc9-2d76-4457-b006-8db2bda88d72"},
                {"username", "Nom d'utilisateur 1"}
            }),
            json::object({
                {"id", "ee41427e-5df9-4e44-88c5-028b08099aad"},
                {"username", "xd"}
            }),
            json::object({
                {"id", "64ea262e-ec4f-4b4a-a30c-455e95fefa2f"},
                {"username", "wtttttttttttt"}
            })
        })}
    };

    int size = 0;

    for (int i = 0; i < list["list"].size(); i++) {
        std::string id = list["list"][i]["id"];
        std::string username = list["list"][i]["username"];

        sf::Text server;
        server.setString(username);
        server.setFont(font);
        server.setCharacterSize(20);
        server.setPosition(50, 100 + size);

        texts.push_back(server);

        Button* joinButton = new Button(font, "Join");
        joinButton->setDefaultBackgroundColor(sf::Color(0x52BE80FF));
        joinButton->setHoverBackgroundColor(sf::Color(0x27AE60FF));
        joinButton->setPosition(sf::Vector2f(250, 100 + size));
        joinButton->setSize(sf::Vector2f(100.f, 25.f));

        buttons.push_back(joinButton);

        size = size + 30;

        // add if i > 20 -> 2 columns
    }

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                quitButton->hover(localPosition);
                createButton->hover(localPosition);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                if (quitButton->hover(localPosition))
                    window->close();
            }
        }

        window->clear();

        window->draw(background);

        for (int i = 0; i < buttons.size(); i++) {
            window->draw(texts[i]);
            buttons[i]->draw(window);
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

void Multiplayer::joinGame()
{

}