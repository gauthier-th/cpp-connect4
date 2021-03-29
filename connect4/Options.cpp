#include <iostream>
#include "Options.h"
#include "TextBox.h"

void Options::display()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(650, 650), "Connect 4", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

    sf::Font font;
    if (!font.loadFromFile("resources/Lato-Regular.ttf"))
        std::cout << "Unable to load font file" << std::endl;

    sf::RectangleShape background(sf::Vector2f(650.f, 650.f));
    background.setFillColor(sf::Color(0x0089E3FF));

    TextBox* textbox = new TextBox(font);
    textbox->setPosition(sf::Vector2f(190.f, 110.f));

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
                textbox->hover(localPosition, window);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                if (textbox->hover(localPosition, window))
                    textbox->focus();
                else
                    textbox->blur();
            }
            if (event.type == sf::Event::TextEntered)
            {
                textbox->text(event.text.unicode);
            }
        }

        window->clear();
        window->draw(background);
        textbox->draw(window);
        window->display();
    }
}