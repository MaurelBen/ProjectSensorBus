#include "../include/WindSensor.h"

WindSensor::WindSensor(const std::string& name) : ISensor(name)
{
	updateValues();
}
WindSensor::~WindSensor() {

}

std::string WindSensor::valueToString() const
{
	std::string text = std::format("Wind direction :{:.2f} / {:.2f} at {:.2f} km/h ", wind.dir.x, wind.dir.y, wind.speed);
	return text;
}

void WindSensor::updateValues()
{	
	// 2d value normalized between 1 and -1
	float x =(float) (rand() % 101 - 50.0)/100.0f;
	float y =(float) (rand() % 101 - 50.0)/100.0f;
	wind.dir.x = x;
	wind.dir.y = y;

	wind.speed = (float) (rand() % 100);
	updateLastUpdate();
}

WindSensor::WindSensor(const std::string& name, std::chrono::milliseconds dt):ISensor(name) {
	setUpdateDeltaTime(dt);
}
