#include "ConfigReader.h"

ConfigReader::ConfigReader(std::string dir) {
    dirConfig = dir+"\\.conf";
    ConfigReader::readFile();
}

void ConfigReader::readFile() {
    std::ifstream fileConfig(dirConfig);
    if (fileConfig.is_open()) {
        std::string line;
        while (getline(fileConfig, line)) {
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
            if (line[0] == '#' || line.empty()) {
                continue;
            }
            else if (line.find('#')) {
                line = line.substr(0, line.find('#'));
            }
            std::istringstream iss(line);
            std::string strr;
            while (getline(iss, strr, ',')) {
                auto delimiterPos = strr.find("=");
                auto name = strr.substr(0, delimiterPos);
                std::string value = strr.substr(delimiterPos + 1);
                // std::cout << name << " " << value << '\n';
                data[name] = value;
            }
        }
    }
    else {
        std::cerr << "Couldn't open config file for reading.\n";
    }
}

std::string ConfigReader::getValue(std::string value) {
    std::unordered_map<std::string, std::string>::iterator it;
    it = data.find(value);
    if (it != data.end())
    {
        return data.at(value);
    }
    return "not_found";
}
