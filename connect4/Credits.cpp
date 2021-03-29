#include <iostream>
#include "Credits.h"
#include "Button.h"

void Credits::display()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(650, 650), "Connect 4 - Crédits", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

    sf::Font font;
    if (!font.loadFromFile("resources/Lato-Regular.ttf"))
        std::cout << "Unable to load font file" << std::endl;

    sf::RectangleShape background(sf::Vector2f(650.f, 650.f));
    background.setFillColor(sf::Color(0x0089E3FF));

    sf::Text text = sf::Text();
    text.setString("Created by Gauthier & Tom\n\n2021");
    text.setFont(font);
    text.setCharacterSize(20);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(650/2, 650/2));

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
        window->draw(text);
        window->display();
    }
}


