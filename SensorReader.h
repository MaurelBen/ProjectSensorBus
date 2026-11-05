#pragma once
#include <string>
#include "ISensor.h"
using namespace std::chrono;

// Class to read sensor data
class SensorReader
{
public:
	SensorReader();
	// get the value of the sensor and update the timestamp
	void readSensor(ISensor& sensor);
	// print with a correct format value and date of the sensor last read
	void printValues() const;
	std::string getValues() const;
	std::chrono::system_clock::time_point getTimestamp() const;

private:

	std::string sensorName;
	std::string sensorValue;
	std::chrono::system_clock::time_point timestamp;
	std::string timestampToString() const;

};
	
