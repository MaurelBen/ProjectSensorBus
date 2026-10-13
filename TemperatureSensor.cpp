#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(const std::string& name) :
	ISensor(name) {
	updateValues();
}

TemperatureSensor::~TemperatureSensor() {
}

void TemperatureSensor::updateValues() {
	// Random value between 0 et 50
	value = rand()%51; 
}

std::string TemperatureSensor::valueToString() const {
	
	return std::to_string(value) + " degre";
}
