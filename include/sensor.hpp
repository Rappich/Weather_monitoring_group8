#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "sensorData.hpp"
#include <string>
#include <random>

class Sensor
{
private:
    // identifier for the sensor
    int id;

    // to implement min/max in sensors
    double min, max;

    // holds the latest sensor data
    SensorData data;

    // random number generator using mt19937 instead of rand for thread safety
    std::mt19937 rng;

public:
    // constructor
    Sensor(int sensorID);

    // return sensor ID
    int getID() const;

    // generates and retursns sensor data
    virtual double getData();

    // simulates reading data from the sensor
    void readData();
};

#endif
