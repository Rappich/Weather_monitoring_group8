#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "sensorData.hpp"
#include <string>

class Sensor
{
private:
    // identifier for the sensor
    int id;

    // holds the latest sensor data
    SensorData data;

public:
    // constructor
    Sensor(int sensorID);

    // return sensor ID
    int getID() const;

    // generates and retursns sensor data
    int getData();

    // simulates reading data from the sensor
    void readData();
};

#endif
