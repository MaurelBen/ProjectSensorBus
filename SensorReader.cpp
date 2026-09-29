#include "SensorReader.h"
#include <iostream>
#include <format>


SensorReader::SensorReader(const std::string& name)
    : sensorName(name), sensorValue("0"), timestamp(std::chrono::system_clock::now())
{
}

void SensorReader::readSensor(ISensor& sensor) {
    sensorValue = sensor.valueToString();
    timestamp = std::chrono::system_clock::now();
}

void SensorReader::printValues() const
{
    
    std::cout << sensorName << " : " << sensorValue << " at " << timestampToString() << std::endl;
}

std::chrono::system_clock::time_point SensorReader::getTimestamp() const {
    return timestamp;
}

std::string SensorReader::timestampToString() const {
    return std::format("{:%H:%M:%S}", timestamp);
}
