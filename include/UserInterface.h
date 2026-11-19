#pragma once
#include "SensorManager.h"
#include "TemperatureSensor.h"

enum class Action { Quit = 0, AddSensor = 1, RemoveSensor = 2, PrintState = 3, DisplaySensorValue = 4};

class UserInterface {
public:
    explicit UserInterface();
    explicit UserInterface(std::unique_ptr<SensorManager> manager) : m_manager(std::move(manager)) {}
    void run();

private:
    void showMenu() const;
    int readInt(const std::string& prompt) const;
    void handleAdd();
    void handleRemove();
    void handleDump() const;
    void handleDisplay() const;

    std::unique_ptr<SensorManager> m_manager;
};


