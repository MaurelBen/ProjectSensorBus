#include "SensorReader.h"
#include <iostream>
#include <format>

static const std::chrono::time_zone* const timezone = std::chrono::current_zone();

static std::string formatTime(std::chrono::system_clock::time_point tp) {
    using namespace std::chrono;
    // heure locale, tronquée à la milliseconde
    zoned_time local{ timezone, floor<milliseconds>(tp) };
    return std::format("{:%H:%M:%S}", local);
}

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
    using namespace std::chrono;

    // heure de lecture : locale, tronquée à la milliseconde
    zoned_time readAt{ timezone, floor<milliseconds>(system_clock::now()) };
    std::cout << std::format("{:<12} : {:>6} | lastUpdate {} | lu {:%H:%M:%S}\n",
        sensorName, sensorValue, timestampToString(), readAt);

}
std::string SensorReader::getValues()  const
{
    using namespace std::chrono;

    // heure de lecture : locale, tronquée à la milliseconde
    zoned_time readAt{ timezone, floor<milliseconds>(system_clock::now()) };
    return std::format("{:<12} : {:>6} | lastUpdate {} | lu {:%H:%M:%S}\n",
        sensorName, sensorValue, timestampToString(), readAt);

}

std::chrono::system_clock::time_point SensorReader::getTimestamp() const {
    return timestamp;
}

std::string SensorReader::timestampToString() const {
    using namespace std::chrono;
      // initialisée une seule fois
    zoned_time local{ timezone, floor<milliseconds>(timestamp) };
    return std::format("{:%H:%M:%S}", local);
   // return std::format("{:%H:%M:%S}", timestamp);
}
