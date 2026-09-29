#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(const std::string& name) :
	name_(name) {
	updateValues();
}

TemperatureSensor::~TemperatureSensor() {
	
}

void TemperatureSensor::updateValues() {
	// Default value
	value = 0.0; 
}

std::string TemperatureSensor::valueToString() const {
	
	return std::to_string(value) + " degre";
}
