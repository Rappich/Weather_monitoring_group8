#include "dataStatistics.hpp"
#include <limits>
#include "measurementData.hpp"

DataStatistics::DataStatistics() {}

// Beräkna alla statistikvärden
void DataStatistics::calculateAll(std::queue<SensorData> &data)
{
    if (data.empty())
    {
        return;
    }

    auto first = data.front();

    temperature.avg = 0;
    windspeed.avg = 0;
    humidity.avg = 0;

    temperature.max = first.temperature;
    windspeed.max = first.windspeed;
    humidity.max = first.humidity;

    temperature.min = first.temperature;
    windspeed.min = first.windspeed;
    humidity.min = first.humidity;

    double sum = 0;
    int count = 0;

    std::queue<SensorData> tempQueue = data;

    while (!tempQueue.empty())
    {
        auto &data = tempQueue.front();

        if (data.temperature < temperature.min)
            temperature.min = data.temperature;
        else if (data.temperature > temperature.max)
            temperature.max = data.temperature;

        if (data.humidity < humidity.min)
            humidity.min = data.humidity;
        else if (data.humidity > humidity.max)
            humidity.max = data.humidity;

        if (data.windspeed < windspeed.min)
            windspeed.min = data.windspeed;
        else if (data.windspeed > windspeed.max)
            windspeed.max = data.windspeed;

        tempQueue.pop();
        ++count;
    }

    temperature.avg /= count;
    windspeed.avg /= count;
    humidity.avg /= count;
}
const MeasurementData &DataStatistics::getWindspeed() const noexcept
{
    return avg;
}
const MeasurementData &DataStatistics::getTemperature() const noexcept
{
    return temperature;
}
const MeasurementData &DataStatistics::getHumidity() const noexcept
{
    return humidity;
}
