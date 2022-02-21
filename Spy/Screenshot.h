#pragma once

#define _WIN32_LEAN_AND_MEAN
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <gdiplus.h>
#include <time.h>
#include <direct.h>
#include <fstream>
#pragma comment( lib, "gdiplus" )
using namespace Gdiplus;

class Screenshot
{
public:
	Screenshot(std::string dir);
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	void saveJpeg(std::string nameFile);
	std::string getBase64(std::string nameFile);
	static std::string encodeFromFile(const std::string& inFileName);
	static std::string encode(const std::vector<char>& data);

private:
	std::string dirPath;
	
};

