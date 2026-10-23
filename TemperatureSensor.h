#pragma once
#include "ISensor.h"

class TemperatureSensor : public ISensor {
public:
    TemperatureSensor(const std::string &name);
    TemperatureSensor(const std::string& name, std::chrono::milliseconds dt);
    ~TemperatureSensor();

    // Update the sensor with new values
    void updateValues() override;

    // dump the values on string format
    std::string valueToString() const;

private:
    float value;
};

