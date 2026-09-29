#pragma once
#include "ISensor.h"

class TemperatureSensor : public ISensor {
public:
    TemperatureSensor(const std::string &name);
    ~TemperatureSensor();

    // Update the sensor with new values
    void updateValues() override;

    // dump the values on string format
    std::string valueToString() const;

private:
    std::string name_;
    float value;
};

