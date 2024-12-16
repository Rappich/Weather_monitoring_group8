#include "sensorManager.hpp"

SensorManager::SensorManager() {}

// Generates a specified number of sensors
void SensorManager::generate(unsigned int numSensors)
{
    for (unsigned int i = 0; i < numSensors; ++i)
    {
        sensors.insert({i, Sensor(i)});
    }
    std::cout << numSensors << " sensors initialized.\n";
}

Sensor &SensorManager::getSensor(int id)
{
    return sensors.at(id);
}

void SensorManager::setSensor(unsigned int id, Sensor &sensor)
{
    sensors.insert({id, sensor});
    std::cout << "Sensor with ID " << id << " has been updated.\n";
}
