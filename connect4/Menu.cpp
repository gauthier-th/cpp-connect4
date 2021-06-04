#include <iostream>
#include "Menu.h"
#include "Button.h"
#include "Game.h"
#include "Credits.h"
#include "Options.h"
#include "Multiplayer.h"

void Menu::afficher()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(650, 650), "Connect 4", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

    sf::Cursor defaultCursor;
    sf::Cursor handCursor;
    if (!defaultCursor.loadFromSystem(sf::Cursor::Arrow) || !handCursor.loadFromSystem(sf::Cursor::Hand))
        std::cout << "Unable to load cursor." << std::endl;

    sf::Font font;
    if (!font.loadFromFile("resources/Lato-Regular.ttf"))
        std::cout << "Unable to load font file" << std::endl;

    sf::RectangleShape background(sf::Vector2f(650.f, 650.f));
    background.setFillColor(sf::Color(0x0089E3FF));

    Button buttonJoin = Button(font, "Local");
    buttonJoin.setPosition(sf::Vector2f(220.f, 110.f));

    Button buttonMultiplayer = Button(font, "Multiplayer");
    buttonMultiplayer.setPosition(sf::Vector2f(220.f, 240.f));
    buttonMultiplayer.setDefaultBackgroundColor(sf::Color(0xFBBE2EFF));
    buttonMultiplayer.setHoverBackgroundColor(sf::Color(0xFBBE2ECF));

    Button buttonCredits = Button(font, "Credits");
    buttonCredits.setPosition(sf::Vector2f(220.f, 370.f));

    Button buttonOptions = Button(font, "Options");
    buttonOptions.setPosition(sf::Vector2f(220.f, 500.f));
    buttonOptions.setDefaultBackgroundColor(sf::Color(0xFBBE2EFF));
    buttonOptions.setHoverBackgroundColor(sf::Color(0xFBBE2ECF));

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
                if (buttonJoin.hover(localPosition) || buttonMultiplayer.hover(localPosition) || buttonCredits.hover(localPosition) || buttonOptions.hover(localPosition))
                    window->setMouseCursor(handCursor);
                else
                    window->setMouseCursor(defaultCursor);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                if (buttonJoin.hover(localPosition))
                {
                    window->setVisible(false);
                    Game* game = new Game();
                    game->display();
                    window->setVisible(true);
                }
                if (buttonMultiplayer.hover(localPosition))
                {
                    window->setVisible(false);
                    Multiplayer* multiplayer = new Multiplayer();
                    multiplayer->display();
                    window->setVisible(true);
                }
                if (buttonCredits.hover(localPosition))
                {
                    window->setVisible(false);
                    Credits* credits = new Credits();
                    credits->display();
                    window->setVisible(true);
                }
                if (buttonOptions.hover(localPosition))
                {
                    window->setVisible(false);
                    Options* options = new Options();
                    options->display();
                    window->setVisible(true);
                }
            }
        }

        window->clear();
        window->draw(background);
        buttonJoin.draw(window);
        buttonMultiplayer.draw(window);
        buttonCredits.draw(window);
        buttonOptions.draw(window);
        window->display();
    }
}


