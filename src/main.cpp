#include <iostream>
#include "../include/SensorReader.h"
#include "../include/TemperatureSensor.h"
#include "../include/WindSensor.h"
#include "../include/SensorManager.h"
#include "../include/UserInterface.h"

[[maybe_unused]]  static std::unique_ptr<SensorManager> initSensorsBasic() {
	std::unique_ptr<SensorManager> manager = std::make_unique<SensorManager>();
	manager->add(std::make_unique<TemperatureSensor>("TempSensor", std::chrono::milliseconds(100)));
	manager->add(std::make_unique<TemperatureSensor>("TempSensor2", std::chrono::milliseconds(250)));
	manager->add(std::make_unique<WindSensor>("WindSensor", std::chrono::milliseconds(150)));
	return manager;
}

[[maybe_unused]]  static std::unique_ptr<SensorManager> initSensorsMulti(int nb) {
	std::unique_ptr<SensorManager> manager = std::make_unique<SensorManager>();
	for (int i = 0; i < nb; i++) {
		if(i%2==0)
			manager->add(std::make_unique<TemperatureSensor>("Sensor n"+std::to_string(i), std::chrono::milliseconds((rand() % 5) * 100)));
		else 
			manager->add(std::make_unique<WindSensor>("Sensor n" + std::to_string(i), std::chrono::milliseconds((rand() % 5) * 50)));
	}
	return manager;
}

int main() 
{
	UserInterface ui;
	ui.run();

	return 0;
}
