#pragma once
#include <string>
#include <chrono>
// Interface for a sensor
class ISensor
{
public:
    virtual ~ISensor() = default;
    explicit ISensor(std::string name) :name(name) {};
    
    // Update the sensor with new values
    virtual void updateValues() = 0;
    bool tryUpdate();

    // dump the values on string format
    virtual std::string valueToString() const = 0;
private:
    std::string name;
    std::chrono::milliseconds updateDeltaTime = std::chrono::milliseconds(200); // delta time in ms
    std::chrono::steady_clock::time_point lastUpdate = std::chrono::steady_clock::now();
};

