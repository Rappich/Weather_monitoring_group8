#ifndef DATASTATISTICS_HPP
#define DATASTATISTICS_HPP

#include <queue>
#include "sensorData.hpp"
#include "dataCollector.hpp"
#include "measurementData.hpp"
#include <limits>

class DataStatistics
{
private:
    MeasurementData windspeed;
    MeasurementData temperature;
    MeasurementData humidity;

public:
    // Konstruktor
    DataStatistics() {}

    void calculateAll(const std::queue<SensorData> &data);

    const MeasurementData& getWindspeed() const noexcept;
    const MeasurementData& getTemperature() const noexcept;
    const MeasurementData& getHumidity() const noexcept;
};

#endif
