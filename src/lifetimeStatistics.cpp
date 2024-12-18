#include "lifetimeStatistics.hpp"

LifetimeStatistics::LifetimeStatistics()
{

}

//not currently in use, will be used once database is implemented.
void LifetimeStatistics::calculateAll(const std::queue<SensorData> *data)
{
    if (data->empty())
    {
        return;
    }

    int count = 0;

    std::queue<SensorData> tempQueue = *data;

    while (!tempQueue.empty())
    {
        auto &data = tempQueue.front();

        if (data.temperature < temperature.min)
            temperature.min = data.temperature;
        
        if (data.temperature >= temperature.max)
            temperature.max = data.temperature;

        if (data.humidity < humidity.min)
            humidity.min = data.humidity;
        
        if (data.humidity >= humidity.max)
            humidity.max = data.humidity;

        if (data.windspeed < windspeed.min)
            windspeed.min = data.windspeed;
        
        if (data.windspeed >= windspeed.max)
            windspeed.max = data.windspeed;

        windspeed.avg += data.windspeed;
        temperature.avg += data.temperature;
        humidity.avg += data.humidity;

        windspeed.avg /= 2;
        temperature.avg /= 2;
        humidity.avg /= 2;

        tempQueue.pop();
        ++count;
    }

    temperature.avg /= (double) count;
    windspeed.avg /= (double) count;
    humidity.avg /= (double) count;
}