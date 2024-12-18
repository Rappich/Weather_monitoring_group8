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

    // holds the latest sensor data
    SensorData data;

    // random number generator using mt19937 instead of rand for thread safety
    std::mt19937 rng;

    double avgTemp, avgHumidity, avgWindspeed;
public:
    // constructor
    Sensor(int sensorID);
    Sensor(int sensorID, double avgTemp, double avgHumidity, double avgWindspeed);

    // return sensor ID
    int getID() const;

    // generates and retursns sensor data
    double generateData(double avg);
    double generateData(double avg, double delta);

    const SensorData &getData();
    
    // simulates reading data from the sensor
    void readData();
};

#endif
