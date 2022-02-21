#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using std::istringstream;

class ConfigReader
{
public:
	ConfigReader(std::string dir);
	void readFile();
	std::string getValue(std::string value);
private:
	std::string dirConfig;
	std::unordered_map<std::string, std::string> data;
};

