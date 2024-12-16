#include "sensorManager.hpp"

SensorManager::SensorManager() {}

// Generates a specified number of sensors
void SensorManager::generate(size_t numSensors)
{
    for (size_t i = 0; i < numSensors; ++i)
    {
        sensors[i] = Sensor(i);
    }
    std::cout << numSensors << " sensors initialized.\n";
}

Sensor &SensorManager::getSensor(int id)
{
    return sensors.at(id);
}

void SensorManager::setSensor(int id, Sensor &sensor)
{
    sensors[id] = sensor;
    std::cout << "Sensor with ID " << id << " has been updated.\n";
}
