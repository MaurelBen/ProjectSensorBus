#include "SensorReader.h"
#include <iostream>
#include <format>


SensorReader::SensorReader()
    : sensorName("none"), sensorValue("0"), timestamp(std::chrono::system_clock::now())
{
}

void SensorReader::readSensor(ISensor& sensor) {
    sensorName = sensor.getName();
    sensorValue = sensor.valueToString();
    timestamp = sensor.getTime();
}

void SensorReader::printValues() const
{
    std::cout  << sensorName << " : " << sensorValue << " at " << timestampToString() 
        << " read at " << std::format("{:%H:%M:%S}", std::chrono::system_clock::now()) 
        << std::endl;
}

std::chrono::system_clock::time_point SensorReader::getTimestamp() const {
    return timestamp;
}

std::string SensorReader::timestampToString() const {
    return std::format("{:%H:%M:%S}", timestamp);
}
