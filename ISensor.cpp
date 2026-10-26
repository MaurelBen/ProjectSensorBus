#include "ISensor.h"


const bool ISensor::tryUpdate() const {
	const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    if (now - lastUpdate >= updateDeltaTime) {
        return true;
    }
    return false;
}

const std::string ISensor::getName() {
    return name;
}
std::chrono::system_clock::time_point ISensor::getTime() const {
    return lastUpdate;
}

void ISensor::setUpdateDeltaTime(std::chrono::milliseconds dt) {
    updateDeltaTime = dt;
}
void ISensor::updateLastUpdate() {
    lastUpdate = std::chrono::system_clock::now();
}
std::chrono::milliseconds ISensor::getUpdateDt() const{
    return updateDeltaTime;
}