#include <iostream>
#include "Menu.h"
#include "Button.h"

void Menu::afficher()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(650, 650), "Connect 4", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

    sf::Font font;
    if (!font.loadFromFile("resources/Lato-Regular.ttf"))
    {
        std::cout << "Unable to load font file" << std::endl;
    }

    sf::RectangleShape background(sf::Vector2f(650.f, 650.f));
    background.setFillColor(sf::Color(0x0089E3FF));

    Button buttonJoin = Button(font, "Join a game");
    buttonJoin.setPosition(sf::Vector2f(220.f, 110.f));

    Button buttonCreate = Button(font, "Create a game");
    buttonCreate.setPosition(sf::Vector2f(220.f, 240.f));
    buttonCreate.setBackgroundColor(sf::Color(0xFBBE2EFF));

    Button buttonCredits = Button(font, "Credits");
    buttonCredits.setPosition(sf::Vector2f(220.f, 370.f));

    Button buttonOptions = Button(font, "Options");
    buttonOptions.setPosition(sf::Vector2f(220.f, 500.f));
    buttonOptions.setBackgroundColor(sf::Color(0xFBBE2EFF));

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(background);
        buttonJoin.draw(window);
        buttonCreate.draw(window);
        buttonCredits.draw(window);
        buttonOptions.draw(window);
        window->display();
    }
}


