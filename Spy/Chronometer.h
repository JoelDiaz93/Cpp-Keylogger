#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <memory>
#include <functional>
#include <iomanip>
#include <iostream>
#include <windows.h> 

class Chronometer
{
public:
	Chronometer(int minAlarm);
	void setAlarm();
	bool alarmChrono();
	std::string formatTime(const std::chrono::system_clock::time_point& time, const std::string& format);

private:
	int lapse;
	std::chrono::system_clock::time_point alarm;
	std::chrono::seconds time = std::chrono::seconds::zero();
};
