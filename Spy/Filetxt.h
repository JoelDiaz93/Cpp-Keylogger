#pragma once
#include "string" 
#include <fstream>
#include <iostream>

class Filetxt
{
public:
	Filetxt(std::string dirKey, std::string dirMouse);
	void saveFile(std::string type, std::string name, std::string date, std::string time, std::string window, std::string content);

private:
	std::string dirPathKey;
	std::string dirPathMouse;
};

