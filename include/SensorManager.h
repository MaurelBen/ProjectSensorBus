#pragma once
#include <iostream>
#include "ISensor.h"
#include "SensorReader.h"
#include <numeric>
#include <thread>
#include <shared_mutex>

using namespace std::chrono;

class SensorManager
{
public:
	SensorManager();
	~SensorManager() = default;

	// add a sensor in the sensor list
	void add(std::unique_ptr<ISensor> sensor);
	// remove a sensor in the sensor list
	void remove(std::unique_ptr<ISensor> sensor);
	void removeLast();
	// dump info on the sensor (wip)
	void dumpState() const;

	// Update mono and multithread
	/*
	void LoopUpdateSensors(milliseconds duration);
	void LoopUpdateSensorsMt(milliseconds duration);
	*/
	void displayValue() const;
	void displayValueMtBuffered() const;

private:
	mutable std::shared_mutex m_mutex;
	std::vector<std::unique_ptr<ISensor>> sensors;
	mutable  std::vector<std::string> displayBuffer;
	void updateSensors();
	std::vector<std::jthread> m_workers;
};

