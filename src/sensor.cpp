#include "sensor.hpp"

Sensor::Sensor(int sensorID) : id(sensorID), data()
{
    std::random_device rd;
    rng = std::mt19937(rd());
}

int Sensor::getID() const
{
    return id;
}

double Sensor::getRandomValue(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(rng);
}

const SensorData &Sensor::getData() const
{
    return data;
}

SensorData Sensor::generateData(double avgTemp, double avgHum, double avgWind)
{
    SensorData generatedData;

    generatedData.temperature = std::clamp(
        getRandomValue(avgTemp - 5.0, avgTemp + 5.0),
        GLOBAL_MIN_TEMPERATURE, GLOBAL_MAX_TEMPERATURE);

    generatedData.humidity = std::clamp(
        getRandomValue(avgHum - 10.0, avgHum + 10.0),
        GLOBAL_MIN_HUMIDITY, GLOBAL_MAX_HUMIDITY);

    generatedData.windspeed = std::clamp(
        getRandomValue(avgWind - 3.0, avgWind + 3.0),
        GLOBAL_MIN_WIND, GLOBAL_MAX_WIND);

    generatedData.timestamp = std::time(nullptr);
    return generatedData;
}

void Sensor::readData()
{
    data = generateData((GLOBAL_MIN_TEMPERATURE + GLOBAL_MAX_TEMPERATURE) / 2,
                        (GLOBAL_MIN_HUMIDITY + GLOBAL_MAX_HUMIDITY) / 2,
                        (GLOBAL_MIN_WIND + GLOBAL_MAX_WIND) / 2);
}
