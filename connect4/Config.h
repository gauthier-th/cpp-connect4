#pragma once
#include <string>

class Config
{
private:
	std::string serverIp = "play.gauthierth.fr";
	std::string username = "Jean Peplu";
	std::string filename = "connect4.conf";
public:
	Config();
	Config(std::string _filename);
	void setServerIp(std::string _serverIp);
	void setUsername(std::string _username);
	std::string getServerIp();
	std::string getUsername();
	void load();
	void save();
};
