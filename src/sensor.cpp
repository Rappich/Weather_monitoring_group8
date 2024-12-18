#include "sensor.hpp"

Sensor::Sensor(int sensorID) : id(sensorID), data()
{
    // seed to add randomness
    std::random_device rd;
    rng = std::mt19937(rd());
}

Sensor::Sensor(int sensorID, double avgTemp, double avgHumidity, double avgWindspeed) 
    : id(sensorID), data(), avgTemp(avgTemp), avgHumidity(avgHumidity), avgWindspeed(avgWindspeed)
{
    // seed to add randomness
    std::random_device rd;
    rng = std::mt19937(rd());
}

int Sensor::getID() const
{
    return id;
}

double Sensor::generateData(double avg, double delta)
{
    static thread_local std::mt19937 generator;
    std::uniform_real_distribution<double> distribution(avg - delta, avg + delta);
    return distribution(generator);
}

double Sensor::generateData(double avg)
{
    static thread_local std::mt19937 generator;
    std::uniform_real_distribution<double> distribution(avg - 5, avg + 5);
    return distribution(generator);
}


const SensorData &Sensor::getData()
{
    return this->data;
}

void Sensor::readData()
{
    data.temperature = generateData(avgTemp, 5); // Temperature: -40 to 40
    if (avgHumidity >= 90)
        avgHumidity -= 10;
    if (avgHumidity <= 10)
        avgHumidity += 10;
    data.humidity = generateData(avgHumidity, 10);     // Humidity: 0% to 100%
    if (avgWindspeed < 0)
        avgWindspeed = 5;
    data.windspeed = generateData(avgWindspeed, 5);     // Wind speed: 0 to 30 m/s
}
