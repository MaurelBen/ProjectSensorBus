#pragma once
#include <iostream>
#include "ISensor.h"
#include "SensorReader.h"
#include <thread>
using namespace std::chrono;

class SensorManager
{
public:
	SensorManager() = default;
	~SensorManager() = default;

	// add a sensor in the sensor list
	void add(std::unique_ptr<ISensor> sensor);
	// remove a sensor in the sensor list
	void remove(std::unique_ptr<ISensor> sensor);
	// dump info on the sensor (wip)
	void dumpState() const;

	// Update mono and multithread
	void LoopUpdateSensors(milliseconds time);
	void LoopUpdateSensorsMt(milliseconds time);

private:
	std::vector<std::unique_ptr<ISensor>> sensors;
	mutable  std::vector<std::string> displayBuffer;
	void updateSensors();
	void displayValue() const;
	void displayValueMtBuffered() const;
};

