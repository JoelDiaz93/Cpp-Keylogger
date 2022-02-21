#include "Date.h"

Date::Date() {
	GetLocalTime(&t);
	day = t.wDay;
	month = t.wMonth;
	year = t.wYear;
	dayName = t.wDayOfWeek;
}

void Date::setDateInt() {
	GetLocalTime(&t);
	day = t.wDay;
	month = t.wMonth;
	year = t.wYear;
	dayName = t.wDayOfWeek;
}

void Date::clearDate() {
	sYear.clear();
	sMonth.clear();
	sDay.clear();
}

void Date::setDateString() {
	Date::clearDate();
	sYear = std::to_string(year);
	//Month
	if (std::to_string(month).length() == 1) {
		sMonth += "0" + std::to_string(month);
	}
	else {
		sMonth += std::to_string(month);
	}
	//Day
	if (std::to_string(day).length() == 1) {
		sDay += "0" + std::to_string(day);
	}
	else {
		sDay += std::to_string(day);
	}
}

std::string Date::getNow() {
	Date::setDateString();	
	return (sYear + "-" + sMonth + "-" + sDay);
}

std::string Date::getNumbers() {
	Date::setDateString();
	return (sYear+ sMonth+ sDay);
}

std::string Date::Dayofweek()
{
	std::string name;
	switch (dayName)
	{
	case 0: name = "[DOMINGO]"; break;
	case 1: name = "[LUNES]"; break;
	case 2: name = "[MARTES]"; break;
	case 3: name = "[MIERCOLES]"; break;
	case 4: name = "[JUEVES]"; break;
	case 5: name = "[VIERNES]"; break;
	case 6: name = "[SABADO]"; break;
	default:
		name = "[DESCONOCIDO]";
	}
	return name;
}