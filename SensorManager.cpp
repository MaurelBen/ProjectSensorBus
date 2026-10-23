#include "SensorManager.h"
#define SLEEPINGTIME std::chrono::milliseconds(100)

void SensorManager::add(std::unique_ptr<ISensor> sensor) {
	if (sensor == nullptr) return;
	sensors.push_back(std::move(sensor));
	return;
}
void SensorManager::remove(std::unique_ptr<ISensor> sensor) {
	std::erase(sensors,sensor);
	return;
}

void SensorManager::dumpState() const{
	std::string dump = " actuellement dans le manager il y a " + std::to_string(sensors.size());
	std::cout << dump << std::endl;
	for (const auto& s : sensors) {
		std::cout << " - " << s->getName() << std::endl;
	}
	return;
}

void SensorManager::LoopUpdateSensors(std::chrono::milliseconds time) {
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point end = start+time;
	std::cout << " ---- New loop ---- " << std::endl;
	while (start <= end) {
		updateSensors();
		displayValue();
		std::this_thread::sleep_for(SLEEPINGTIME);
		start = std::chrono::system_clock::now();
		std::cout << " ---- New loop ---- " << std::endl;
	}
}

void SensorManager::updateSensors()
{
	for (auto& sensor : sensors) {
		if (sensor->tryUpdate()) {
			std::cout << "sensor " << sensor->getName() << " has been updated" << std::endl;
			sensor->updateValues();
		}
		else {
			std::cout << "sensor " << sensor->getName() << " update failed" << std::endl;
		}
	}
}

void SensorManager::displayValue() const
{
	SensorReader reader= SensorReader();
	for (auto& sensor : sensors) {
		reader.readSensor(*sensor);
		reader.printValues();
	}
}
