#include "WindowsData.h"

WindowsData::WindowsData() {
	DWORD sizeUser = UNLEN + 1;
	DWORD sizeComputer = UNLEN + 1;
	char cUser[300];
	char cComputer[300];
	if (GetUserNameA(cUser, &sizeUser)) {
		userName = cUser;
	}
	else {
		userName = "Unknow";
	}

	if (GetComputerNameA(cComputer, &sizeComputer)) {
		computerName = cComputer;
	}
	else {
		computerName = "Unknow";
	}
	id = userName + "-" + computerName;
}

string WindowsData::getUserNamer() {
	return userName;
}

string WindowsData::getComputerName() {
	return computerName;
}

string WindowsData::getID() {
	return id;
}