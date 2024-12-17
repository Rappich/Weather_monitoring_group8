#include "dataStatistics.hpp"
#include <limits>
#include "measurementData.hpp"
#include <iostream>

DataStatistics::DataStatistics() {}

// Beräkna alla statistikvärden
void DataStatistics::calculateAll(const std::queue<SensorData> *data)
{
    if (data->empty())
    {
        return;
    }

    auto first = data->front();

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

const MeasurementData DataStatistics::getWindspeed() const noexcept
{
    return windspeed;
}
const MeasurementData DataStatistics::getTemperature() const noexcept
{
    return temperature;
}
const MeasurementData DataStatistics::getHumidity() const noexcept
{
    return humidity;
}

void DataStatistics::displayStatistics()
{
    // Print the statistics using DataStatistics
    std::cout << "Displaying statistics:" << std::endl;
    std::cout << "Average temperature: " << temperature.avg << std::endl;
    std::cout << "Average humidity: " << humidity.avg << std::endl;
    std::cout << "Avrige windspeed" << windspeed.avg << std::endl;
}

/* void DataStatistics::displayAvailableData()
{
    //
    std::cout << "Displaying last measured data..." << std::endl;
   // std::cout << "Temperature: " << dataCollector.getTemperature() << std::endl;
   // std::cout << "Humidity: " << dataCollector.getHumidity() << std::endl;
    std::cout << "Windspeed: " << dataCollector.getWindspeed() << std::endl;
} */