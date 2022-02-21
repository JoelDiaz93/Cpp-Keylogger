#pragma once
#include <iostream>
#include <Windows.h>
#include <Lmcons.h>
#include "string" 
#include <sstream>

class KeyboardHook
{
public:
	static KeyboardHook& Instance() {
		static KeyboardHook keyboardHook;
		return keyboardHook;
	}
	void InstallHook();
	void UninstallHook();
	MSG msg;
	int Messsages();
	HHOOK MyKeyboardHook;

private:

};