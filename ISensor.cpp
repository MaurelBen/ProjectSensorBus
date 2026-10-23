#include "ISensor.h"


bool ISensor::tryUpdate() {
	const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    if (now - lastUpdate >= updateDeltaTime) {
        return true;
    }
    return false;
}

std::string ISensor::getName() {
    return name;
}
std::chrono::system_clock::time_point ISensor::getTime() {
    return lastUpdate;
}

void ISensor::setUpdateDeltaTime(std::chrono::milliseconds dt) {
    updateDeltaTime = dt;
}
void ISensor::updateLastUpdate() {
    lastUpdate = std::chrono::system_clock::now();
}