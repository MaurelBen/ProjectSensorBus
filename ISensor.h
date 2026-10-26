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

    void setUpdateDeltaTime(std::chrono::milliseconds dt);
    const bool tryUpdate() const;

    // dump the values on string format
    virtual std::string valueToString() const = 0;
    const std::string getName();
    std::chrono::system_clock::time_point getTime()const;
    void updateLastUpdate();
     std::chrono::milliseconds getUpdateDt() const;
private:
    std::string name;
    std::chrono::milliseconds updateDeltaTime = std::chrono::milliseconds(200); // delta time in ms
    std::chrono::system_clock::time_point lastUpdate = std::chrono::system_clock::now();
};

