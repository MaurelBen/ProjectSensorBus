#include <iostream>
#include "SensorReader.h"
#include "TemperatureSensor.h"
#include "WindSensor.h"

int main()
{
	SensorReader reader("TemperatureReader");
	TemperatureSensor tempSensor("TempSensor");
	std::cout << tempSensor.valueToString() << std::endl;
	reader.readSensor(tempSensor);
	reader.printValues();

	WindSensor windSensor("WindSensor");
	SensorReader reader2("WindReader");
	reader2.readSensor(windSensor);
	reader2.printValues();

	
    return 0;
}