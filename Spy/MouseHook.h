#pragma once
#include <iostream>
#include <Windows.h>
#include <Lmcons.h>
#include "string" 
#include <sstream>

class MouseHook {
public:
	//single ton
	static MouseHook& Instance() {
		static MouseHook myHook;
		return myHook;
	}
	HHOOK hook; // handle to the hook	
	void InstallHook(); // function to install our hook
	void UninstallHook(); // function to uninstall our hook

	MSG msg; // struct with information about all messages in our queue
	int Messsages(); // function to "deal" with our messages 
};