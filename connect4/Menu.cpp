#include "Menu.h"

void Menu::afficher()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(650, 650), "Connect 4", sf::Style::None + sf::Style::Titlebar + sf::Style::Close, settings);

    sf::Font font;
    if (!font.loadFromFile("resources/Lato-Regular.ttf"))
        throw std::exception("Error while load the font");

    sf::RectangleShape background(sf::Vector2f(650.f, 650.f));
    background.setFillColor(sf::Color(0x0089E3FF));

    sf::RectangleShape buttonJoin;
    buttonJoin.setSize(sf::Vector2f(210.f, 50.f));
    buttonJoin.setFillColor(sf::Color(0xFF341AFF));
    buttonJoin.setPosition(220.f, 130.f);
    sf::Text textJoin;
    textJoin.setString("Hello world");
    textJoin.setFont(font);
    textJoin.setCharacterSize(24);
    textJoin.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = textJoin.getLocalBounds();
    textJoin.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    textJoin.setPosition(325.f, 145.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.draw(buttonJoin);
        window.draw(textJoin);
        window.display();
    }
}


