#include "dataStatistics.hpp"
#include <limits>
#include "measurementData.hpp"

DataStatistics::DataStatistics() {}

void DataStatistics::calculateAll(const std::queue<SensorData> &data)
{
    if (data.empty())
    {
        min = max = avg = 0;
        return;
    }

    SensorData first = data.front();
    min = max = first.temperature;
    double sum = 0;
    int count = 0;

    std::queue<SensorData> tempQueue = data;

    while (!tempQueue.empty())
    {
        double value = tempQueue.front().temperature;
        if (value < min)
            min = value;
        if (value > max)
            max = value;
        sum += value;

        tempQueue.pop();
        ++count;
    }

    avg = sum / count;
}
const MeasurementData &DataStatistics::getWindspeed() const noexcept
{
    return windspeed;
}
const MeasurementData &DataStatistics::getTemperature() const noexcept
{
    return temperature;
}
const MeasurementData &DataStatistics::getHumidity() const noexcept
{
    return humidity;
}
