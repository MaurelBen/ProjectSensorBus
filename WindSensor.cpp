#include "WindSensor.h"

WindSensor::WindSensor(const std::string& name) : ISensor(name)
{
	updateValues();
}
WindSensor::~WindSensor() {

}

std::string WindSensor::valueToString() const
{
	std::string text = "Wind direction :" + std::to_string(wind.dir.x) + " / " + std::to_string(wind.dir.y) + " at " + std::to_string(wind.speed) + "km/h ";
	return text;
}

void WindSensor::updateValues()
{	
	// 2d value normalized between 1 and -1
	float x = (rand() % 101 - 50.0)/100.0;
	float y = (rand() % 101 - 50.0)/100.0;
	wind.dir.x = x;
	wind.dir.y = y;

	wind.speed = rand() % 100;
}
