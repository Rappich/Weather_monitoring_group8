#include "sensor.hpp"

Sensor::Sensor(int sensorID) : id(sensorID), data()
{
    // seed to add randomness
    std::random_device rd;
    rng = std::mt19937(rd());
}

int Sensor::getID() const
{
    return id;
}

double Sensor::getData()
{
    std::uniform_real_distribution<double> distribution(-40.0, 40.0);
    return distribution(rng);
}

void Sensor::readData()
{
    data.temperature = getData();
    data.humidity = getData();
    data.windspeed = getData();
}