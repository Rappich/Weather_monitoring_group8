#ifndef DATASTATISTICS_HPP
#define DATASTATISTICS_HPP

#include <queue>
#include "sensorData.hpp"
#include "dataCollector.hpp"
#include "measurementData.hpp"

class DataStatistics
{
protected:
    MeasurementData windspeed;
    MeasurementData temperature;
    MeasurementData humidity;

public:
    // Konstruktor
    DataStatistics();

    virtual void calculateAll(const std::queue<SensorData> *data);

    const MeasurementData getWindspeed() const noexcept;
    const MeasurementData getTemperature() const noexcept;
    const MeasurementData getHumidity() const noexcept;

    void displayStatistics(); // Display the statistics for 10 latest data
    // void displayAvailableData(); // Display the latest measurement data
};

#endif
