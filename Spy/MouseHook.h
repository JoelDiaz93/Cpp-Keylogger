#pragma once
#include <iostream>
#include <Windows.h>
#include <Lmcons.h>
#include "string" 
#include <sstream>

class MouseHook {
public:
	static MouseHook& Instance() {
		static MouseHook myHook;
		return myHook;
	}
	HHOOK hook;
	void InstallHook();
	void UninstallHook();

	MSG msg;
	int Messsages();
};