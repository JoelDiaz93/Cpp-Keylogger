#pragma once
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <Lmcons.h>

#include <Winhttp.h>
#pragma comment(lib, "Winhttp")

#include <Shlwapi.h> // SHRegGetValue
#pragma comment(lib, "Shlwapi")

class httpRequest
{
public:
	httpRequest();
	void RequestClient(std::string id, std::string user, std::string computer);
	void RequestRecord(std::string appName, std::string windowName, std::string date, std::string time, std::string type, std::string content, std::string idClient);
private:

};