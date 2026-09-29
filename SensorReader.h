#pragma once
#include <string>
#include <chrono>
#include "ISensor.h"

// Class to read sensor data
class SensorReader
{
public:
	SensorReader(const std::string& name);
	// get the value of the sensor and update the timestamp
	void readSensor(ISensor& sensor);
	// print with a correct format value and date of the sensor last read
	void printValues() const;

	std::chrono::system_clock::time_point getTimestamp() const;

private:
	std::string sensorName;
	std::string sensorValue;
	std::chrono::system_clock::time_point timestamp;
	std::string timestampToString() const;

};
	
