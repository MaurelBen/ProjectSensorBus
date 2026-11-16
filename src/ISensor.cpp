#include "../include/WindSensor.h"


const bool ISensor::tryUpdate() const {
    if (std::chrono::system_clock::now() - lastUpdate >= updateDeltaTime) {
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