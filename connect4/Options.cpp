#include <iostream>
#include "Options.h"
#include "TextBox.h"

void Options::display()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(650, 650), "Connect 4 - Options", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

    sf::Font font;
    if (!font.loadFromFile("resources/Lato-Regular.ttf"))
        std::cout << "Unable to load font file" << std::endl;

    sf::RectangleShape background(sf::Vector2f(650.f, 650.f));
    background.setFillColor(sf::Color(0x0089E3FF));

    sf::Text textUsername = sf::Text();
    textUsername.setString("Pseudo");
    textUsername.setFont(font);
    textUsername.setCharacterSize(24);
    sf::FloatRect textRectUsername = textUsername.getLocalBounds();
    textUsername.setOrigin(textRectUsername.left + textRectUsername.width / 2.0f, textRectUsername.top + textRectUsername.height / 2.0f);
    textUsername.setPosition(sf::Vector2f(650/2, 90));

    TextBox* textboxUsername = new TextBox(font);
    textboxUsername->setPosition(sf::Vector2f(190.f, 120.f));
    textboxUsername->setCharacterSize(24);

    sf::Text textIp = sf::Text();
    textIp.setString("Serveur");
    textIp.setFont(font);
    textIp.setCharacterSize(24);
    sf::FloatRect textRectIp = textIp.getLocalBounds();
    textIp.setOrigin(textRectIp.left + textRectIp.width / 2.0f, textRectIp.top + textRectIp.height / 2.0f);
    textIp.setPosition(sf::Vector2f(650 / 2, 220));

    TextBox* textboxIp = new TextBox(font);
    textboxIp->setPosition(sf::Vector2f(190.f, 250.f));
    textboxIp->setCharacterSize(24);

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
                textboxUsername->hover(localPosition, window);
                textboxIp->hover(localPosition, window);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                if (textboxUsername->hover(localPosition, window))
                    textboxUsername->focus();
                else
                    textboxUsername->blur();
                if (textboxIp->hover(localPosition, window))
                    textboxIp->focus();
                else
                    textboxIp->blur();
            }
            if (event.type == sf::Event::TextEntered)
            {
                textboxUsername->text(event.text.unicode);
                textboxIp->text(event.text.unicode);
            }
        }

        window->clear();
        window->draw(background);
        window->draw(textUsername);
        window->draw(textIp);
        textboxUsername->draw(window);
        textboxIp->draw(window);
        window->display();
    }
}