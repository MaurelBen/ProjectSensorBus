#include <iostream>
#include "SensorReader.h"
#include "TemperatureSensor.h"
#include "WindSensor.h"
#include "SensorManager.h"

std::unique_ptr<SensorManager> initSensors() {
	std::unique_ptr<SensorManager> manager = std::make_unique<SensorManager>();
	manager->add(std::make_unique<TemperatureSensor>("TempSensor", std::chrono::milliseconds(1000)));
	manager->add(std::make_unique<TemperatureSensor>("TempSensor2", std::chrono::milliseconds(2500)));
	manager->add(std::make_unique<WindSensor>("WindSensor", std::chrono::milliseconds(1000)));
	return manager;
}

int main() 
{
	std::unique_ptr<SensorManager> manager = initSensors();
	manager->dumpState();
	manager->LoopUpdateSensors(std::chrono::milliseconds(5000));
	return 0;
}

/*
int main()
{
	SensorReader reader("TemperatureReader");
	TemperatureSensor tempSensor("TempSensor");
	std::cout << tempSensor.valueToString() << std::endl;
	reader.readSensor(tempSensor);
	reader.printValues();
    return 0;
}*/