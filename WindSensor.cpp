#include "WindSensor.h"

WindSensor::WindSensor(const std::string& name) : ISensor(name)
{
	updateValues();
}
WindSensor::~WindSensor() {

}

std::string WindSensor::valueToString() const
{
	//std::string text =  + " / " + std::to_string(wind.dir.y) + " at " + std::to_string(wind.speed) + "km/h ";
	std::string text = std::format("Wind direction :{:.2f} / {:.2f} at {:.2f} km/h ", wind.dir.x, wind.dir.y, wind.speed);
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
	updateLastUpdate();
}

WindSensor::WindSensor(const std::string& name, std::chrono::milliseconds dt):ISensor(name) {
	setUpdateDeltaTime(dt);
}
