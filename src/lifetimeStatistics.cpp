#include "lifetimeStatistics.hpp"

LifetimeStatistics::LifetimeStatistics()
{

}


void LifetimeStatistics::calculateAll(const std::queue<SensorData> *data)
{
    if (data->empty())
    {
        return;
    }

    double sum = 0;
    int count = 0;

    std::queue<SensorData> tempQueue = *data;

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

    temperature.avg /= (double) count;
    windspeed.avg /= (double) count;
    humidity.avg /= (double) count;
}