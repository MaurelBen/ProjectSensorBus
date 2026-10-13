#pragma once
#include <iostream>
#include "ISensor.h"
class SensorManager
{
public:
	SensorManager() = default;
	~SensorManager() = default;

	void add(ISensor* sensor);
	void remove(ISensor* sensor);
	void dumpState() const;
private:
	std::vector<ISensor*> sensors;
};

