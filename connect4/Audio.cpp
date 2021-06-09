#include "Audio.h"

Audio::Audio()
{
    clickSound.loadFromFile("resources/sound.ogg");
}

void Audio::playClickSound(int _volume)
{
    if (sound.getVolume() != _volume)
    {
        sound.setVolume(_volume);
    }
    sound.setBuffer(clickSound);
    sound.play();
}