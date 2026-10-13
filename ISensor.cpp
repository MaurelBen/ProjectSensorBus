#include "ISensor.h"


bool ISensor::tryUpdate() {
	const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    if (now - lastUpdate >= updateDeltaTime) {
        return true;
    }
    return false;
}

std::string ISensor::getName() {
    return name;
}