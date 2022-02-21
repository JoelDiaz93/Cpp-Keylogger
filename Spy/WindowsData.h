#pragma once
#include <iostream>
#include <Windows.h>
#include <Lmcons.h>
#include "string"

using std::string;

class WindowsData
{
public:
	WindowsData();
	string getUserNamer();
	string getComputerName();
	string getID();

private:
	string userName;
	string computerName;
	string id;
};