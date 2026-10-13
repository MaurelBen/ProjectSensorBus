#pragma once
#include "ISensor.h"

struct Direction {
    float x, y;
    Direction() :x(0), y(0) {};
    Direction(float x, float y) :x(x), y(y) {};
};

struct Wind {
    float speed;
    Direction dir;
    Wind() :speed(0), dir(Direction()) {};
    Wind(float speed, Direction dir) :speed(speed), dir(dir) {};
};

class WindSensor : public ISensor
{   
public:
    WindSensor(const std::string &name);
    ~WindSensor();
    // dump the values on string format
    std::string valueToString() const;
    // Update the sensor with new values
    void updateValues() override;
private:
    Wind wind;
};

