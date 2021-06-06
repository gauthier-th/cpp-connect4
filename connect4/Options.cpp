#include <iostream>
#include "Options.h"
#include "TextBox.h"
#include "Button.h"

Options::Options(Config _config): config(_config)
{
}

void Options::display()
{
    sf::ContextSettings settings;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(650, 650), "Connect 4 - Options", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

    sf::Font font;
    if (!font.loadFromFile("resources/Lato-Regular.ttf"))
        std::cout << "Unable to load font file" << std::endl;

    sf::RectangleShape background(sf::Vector2f(650.f, 650.f));
    background.setFillColor(sf::Color(0x0089E3FF));

    sf::Text textUsername = sf::Text();
    textUsername.setString("Username");
    textUsername.setFont(font);
    textUsername.setCharacterSize(24);
    sf::FloatRect textRectUsername = textUsername.getLocalBounds();
    textUsername.setOrigin(textRectUsername.left + textRectUsername.width / 2.0f, textRectUsername.top + textRectUsername.height / 2.0f);
    textUsername.setPosition(sf::Vector2f(650/2, 90));

    TextBox* textboxUsername = new TextBox(font);
    textboxUsername->setPosition(sf::Vector2f(190.f, 120.f));
    textboxUsername->setCharacterSize(24);
    textboxUsername->setTextContent(config.getUsername());

    sf::Text textIp = sf::Text();
    textIp.setString("Server");
    textIp.setFont(font);
    textIp.setCharacterSize(24);
    sf::FloatRect textRectIp = textIp.getLocalBounds();
    textIp.setOrigin(textRectIp.left + textRectIp.width / 2.0f, textRectIp.top + textRectIp.height / 2.0f);
    textIp.setPosition(sf::Vector2f(650 / 2, 220));

    TextBox* textboxIp = new TextBox(font);
    textboxIp->setPosition(sf::Vector2f(190.f, 250.f));
    textboxIp->setCharacterSize(24);
    textboxIp->setTextContent(config.getServerIp());

    Button* saveButton = new Button(font, "Save");
    saveButton->setDefaultBackgroundColor(sf::Color(26, 196, 77));
    saveButton->setHoverBackgroundColor(sf::Color(59, 235, 111));
    saveButton->setPosition(sf::Vector2f(650 / 2 - 210 / 2, 350.f));

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
                textboxUsername->hover(localPosition, window);
                textboxIp->hover(localPosition, window);
                quitButton->hover(localPosition);
                saveButton->hover(localPosition);
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
                if (saveButton->hover(localPosition)) {
                    config.setUsername(textboxUsername->getTextContent());
                    config.setServerIp(textboxIp->getTextContent());
                    config.save();
                    window->close();
                }
                if (quitButton->hover(localPosition))
                    window->close();
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
        saveButton->draw(window);
        quitButton->draw(window);
        window->display();
    }
}