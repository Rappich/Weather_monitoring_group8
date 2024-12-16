#ifndef SENSORMANAGER_HPP
#define SENSORMANAGER_HPP

#include "sensor.hpp"
#include <map>
#include <iostream>

class SensorManager
{
private:
    // map of sensor IDs to Sensor objects
    std::map<unsigned int, Sensor> sensors;

public:
    SensorManager();

    // generates and initializes sensors
    void generate(unsigned int numSensors);

    // retrieves a sensor by ID from sensor class
    Sensor &getSensor(int id);

    // add a sensor to the hashmap
    void setSensor(unsigned int, Sensor &);
};

#endif