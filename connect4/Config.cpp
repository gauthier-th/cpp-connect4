#include "Config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>

Config::Config()
{
	
}


Config::Config(std::string _filename)
{
	this->filename = _filename;
}

void Config::setServerIp(std::string _serverIp)
{
	this->serverIp = _serverIp;
}

void Config::setServerPort(std::string _serverPort)
{
	this->serverPort = _serverPort;
}

void Config::setUsername(std::string _username)
{
	this->username = _username;
}

std::string Config::getServerIp()
{
	return this->serverIp;
}

std::string Config::getServerPort()
{
	return this->serverPort;
}

std::string Config::getUsername()
{
	return this->username;
}

void Config::load()
{
	std::ifstream infile(this->filename);
	std::string line;
	while (std::getline(infile, line))
	{
		if (line.rfind("serverip=", 0) == 0)
			this->serverIp = line.substr(9);
		if (line.rfind("username=", 0) == 0)
			this->username = line.substr(9);
		if (line.rfind("port=", 0) == 0)
			this->serverPort = line.substr(5);
	}
}

void Config::save()
{
	std::ofstream config(this->filename);

	config << "serverip=" << this->serverIp << std::endl;
	config << "username=" << this->username << std::endl;
	config << "port=" << this->serverPort << std::endl;

	config.close();
}