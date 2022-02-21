#include "Chronometer.h"

Chronometer::Chronometer(int minAlarm) {
    lapse = minAlarm;
    Chronometer::setAlarm();
}

void Chronometer::setAlarm() {
    Chronometer::alarm = std::chrono::system_clock::now() + std::chrono::seconds(lapse);
}

bool Chronometer::alarmChrono() {
    while (true) {
        const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        Chronometer::time = duration_cast<std::chrono::seconds>(alarm - now);
        std::cout << time.count() << "s\n";
        
        if (Chronometer::time <= std::chrono::seconds::zero()) {
            std::cout << "TIME ALARM -> " << std::endl;
            break;
        }
        Sleep(1000);
    }
    std::cout << "TIME ALARM -> " << Chronometer::formatTime(alarm, "UTC: %Y-%m-%d %H:%M:%S") << std::endl;
    return true;
}

std::string Chronometer::formatTime(const std::chrono::system_clock::time_point& time, const std::string& format)
{
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    //std::tm tm = *std::gmtime(&tt); //GMT (UTC)
    std::tm tm = *std::localtime(&tt); //Locale time-zone, usually UTC by default.
    std::stringstream ss;
    ss << std::put_time(&tm, format.c_str());
    return ss.str();
}

using namespace std::chrono;