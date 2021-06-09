#pragma once
#include <SFML/Audio.hpp>

class Audio
{
private:
    sf::Sound sound;
    sf::SoundBuffer clickSound;
public:
    Audio();
    void playClickSound(int _volume);
};

