#include "TemperatureSensor.h"
#include <format>

TemperatureSensor::TemperatureSensor(const std::string& name) :
	ISensor(name) {
	updateValues();
}
TemperatureSensor::TemperatureSensor(const std::string& name, std::chrono::milliseconds dt) :
	ISensor(name) {
	setUpdateDeltaTime(dt);
	updateValues();
}

TemperatureSensor::~TemperatureSensor() {
}

void TemperatureSensor::updateValues() {
	// Random value between 0 et 50
	value = (float)(rand()%51); 
	updateLastUpdate();
}

std::string TemperatureSensor::valueToString() const {
	
	return std::format("{:.2f} degre", value);
}
