#include "sensorManager.hpp"

SensorManager::SensorManager() {}

void SensorManager::generate()
{
    for (size_t i = 0; i < 3; i++)
    {
        sensors[i] = Sensor(i);
    }
    std::cout << "Sensors initialized. \n";
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