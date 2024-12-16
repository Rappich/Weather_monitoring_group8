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
<<<<<<< HEAD
//might have to change this function since it now creates a random number between -40 and 40. This works for temperature but not the other data.
double Sensor::getData()
=======

double Sensor::getData(double min, double max)
>>>>>>> 7dda4fc (made changes)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(rng);
}

void Sensor::readData()
{
    data.temperature = getData(-40.0, 40.0); // Temperature: -40 to 40
    data.humidity = getData(0.0, 100.0);     // Humidity: 0% to 100%
    data.windspeed = getData(0.0, 30.0);     // Wind speed: 0 to 30 m/s
}

