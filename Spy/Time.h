#pragma once
#include <Windows.h>
#include <iostream>
#include "string" 
#include <time.h>

class Time {
private:
	SYSTEMTIME t;
	int hours;
	int minutes;
	int seconds;
	std::string sHours;
	std::string sMinutes;
	std::string sSeconds;
public:
	Time();
	void setTimeInt();
	void setTimeString();
	void clearTime();
	std::string getNow();
	std::string getNumbers();
};