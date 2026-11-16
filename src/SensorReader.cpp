#include "../include/SensorReader.h"
#include <iostream>
#include <format>

static const time_zone* const timezone = current_zone();

SensorReader::SensorReader()
    : sensorName("none"), sensorValue("0"), timestamp(system_clock::now())
{
}

void SensorReader::readSensor(ISensor& sensor) {
    sensorName = sensor.getName();
    sensorValue = sensor.valueToString();
    timestamp = sensor.getTime();
}

void SensorReader::printValues() const
{
    // heure de lecture : locale, tronquée à la milliseconde
    zoned_time readAt{ timezone, floor<milliseconds>(system_clock::now()) };
    std::cout << std::format("{:<12} : {:>6} | lastUpdate {} | lu {:%H:%M:%S}\n",
        sensorName, sensorValue, timestampToString(), readAt);

}
std::string SensorReader::getValues()  const
{
    // heure de lecture : locale, tronquée à la milliseconde
   zoned_time readAt{ timezone, floor<milliseconds>(system_clock::now()) };
    return std::format("{:<12} : {:>6} | lastUpdate {} | lu {:%H:%M:%S}\n", sensorName, sensorValue, timestampToString(), readAt);

}

system_clock::time_point SensorReader::getTimestamp() const {
    return timestamp;
}

std::string SensorReader::timestampToString() const {
    // initialisée une seule fois
    return std::format("{:%H:%M:%S}", timestamp);
}
