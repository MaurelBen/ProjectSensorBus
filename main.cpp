#include <iostream>
#include "SensorReader.h"
#include "TemperatureSensor.h"
#include "WindSensor.h"
#include "SensorManager.h"

int main() {
	TemperatureSensor tempSensor("TempSensor");
	WindSensor windSensor("WindSensor");
	WindSensor windSensor2("WindSensor2");

	SensorManager manager;
	manager.add(&tempSensor);
	manager.add(&windSensor);
	manager.dumpState();

	manager.remove(&tempSensor);
	manager.dumpState();

	manager.add(nullptr);
	manager.add(&windSensor2);
	manager.dumpState();
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