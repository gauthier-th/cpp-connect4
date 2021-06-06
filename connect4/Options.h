#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Config.h"

class Options
{
private:
	Config config;
public:
	Options(Config _config);
	void display();
};