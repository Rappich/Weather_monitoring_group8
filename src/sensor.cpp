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
//might have to change this function since it now creates a random number between -40 and 40. This works for temperature but not the other data.
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
