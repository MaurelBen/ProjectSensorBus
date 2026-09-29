#include <iostream>
#include "SensorReader.h"
#include "TemperatureSensor.h"

int main()
{
	SensorReader reader("TemperatureSensor");
	TemperatureSensor tempSensor("TempSensor");
	std::cout << tempSensor.valueToString() << std::endl;
	reader.readSensor(tempSensor);
	reader.printValues();
    return 0;
}