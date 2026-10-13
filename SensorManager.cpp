#include "SensorManager.h"

void SensorManager::add(ISensor *sensor) {
	if (sensor == nullptr) return;
	sensors.push_back(sensor);
	return;
}
void SensorManager::remove(ISensor* sensor) {
	std::erase(sensors,sensor);
	return;
}

void SensorManager::dumpState() const{
	std::string dump = " actuellement dans le manager il y a " + std::to_string(sensors.size());
	std::cout << dump << std::endl;
	for (ISensor *s : sensors) {
		std::cout << " - " << s->getName() << std::endl;
	}
	return;
}