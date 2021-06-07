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
    text.setString("Connect 4 is a study project at ESIREM, created by Gauthier and Tom.\n\nLast update: 06/10/2021");
    text.setFont(font);
    text.setCharacterSize(20);

    Button* quitButton = new Button(font, "Back");
    quitButton->setSize(sf::Vector2f(150.f, 30.f));
    quitButton->setPosition(sf::Vector2f(650 - 150, 650 - 30));

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
        window->draw(text);
        quitButton->draw(window);
        window->display();
    }
}


