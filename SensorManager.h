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

	void add(std::unique_ptr<ISensor> sensor);
	void remove(std::unique_ptr<ISensor> sensor);
	void dumpState() const;
	void LoopUpdateSensors(milliseconds time);
	void LoopUpdateSensorsMt(milliseconds time);

private:
	std::vector<std::unique_ptr<ISensor>> sensors;
	mutable  std::vector<std::string> displayBuffer;
	void updateSensors();
	void displayValue() const;
	void displayValueMtBuffered() const;
};

