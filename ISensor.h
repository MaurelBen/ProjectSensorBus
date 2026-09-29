#pragma once
#include <string>
// Interface for a sensor
class ISensor
{
public:
    virtual ~ISensor() = default;

    // Update the sensor with new values
    virtual void updateValues() = 0;

    // dump the values on string format
    virtual std::string valueToString() const = 0;
};

