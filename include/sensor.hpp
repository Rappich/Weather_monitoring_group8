#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "sensorData.hpp"
#include <string>
#include <random>

constexpr double GLOBAL_MIN_TEMPERATURE = -40.0;
constexpr double GLOBAL_MAX_TEMPERATURE = 40.0;

constexpr double GLOBAL_MIN_HUMIDITY = 0.0;
constexpr double GLOBAL_MAX_HUMIDITY = 100.0;

constexpr double GLOBAL_MIN_WIND = 0.0;
constexpr double GLOBAL_MAX_WIND = 30.0;

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

    double getRandomValue(double min, double max);

    // generates and retursns sensor data
    double getData(double min, double max);
    const SensorData &getData() const;
    // simulates reading data from the sensor
    void readData();

    SensorData generateData(double avgTemp, double avgHum, double avgWind);
};

#endif
