#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h>

class Date {
private:
	SYSTEMTIME t;
	int day;
	int month;
	int year;
	int dayName;
	std::string sDay;
	std::string sMonth;
	std::string sYear;

public:
	Date();
	void setDateInt();
	void setDateString();
	void clearDate();
	std::string getNow();
	std::string getNumbers();
	std::string Dayofweek();
};
