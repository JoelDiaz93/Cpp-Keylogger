#include "Time.h"

Time::Time() {
	GetLocalTime(&t);
	hours = t.wHour;
	minutes = t.wMinute;
	seconds = t.wSecond;
}

void Time::clearTime() {
	sHours.clear();
	sMinutes.clear();
	sSeconds.clear();
}

void Time::setTimeInt() {
	GetLocalTime(&t);
	hours = t.wHour;
	minutes = t.wMinute;
	seconds = t.wSecond;
}

void Time::setTimeString() {
	Time::clearTime();
	if (std::to_string(hours).length() == 1) {
		sHours += "0" + std::to_string(hours);
	}
	else {
		sHours += std::to_string(hours);
	}
	//Minutos
	if (std::to_string(minutes).length() == 1) {
		sMinutes += "0" + std::to_string(minutes);
	}
	else {
		sMinutes += std::to_string(minutes);
	}
	//Segundos
	if (std::to_string(seconds).length() == 1) {
		sSeconds += "0" + std::to_string(seconds);
	}
	else {
		sSeconds += std::to_string(seconds);
	}
}

std::string Time::getNow() {
	Time::setTimeString();
	return (sHours + ":" + sMinutes + ":" + sSeconds);
}

std::string Time::getNumbers() {
	Time::setTimeString();
	return (sHours + sMinutes + sSeconds);
}