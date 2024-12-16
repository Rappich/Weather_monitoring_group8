#ifndef SENSORDATA_HPP
#define SENSORDATA_HPP

struct SensorData
{
    double windspeed;
    double temperature;
    double humidity;

    // timestamp for data generation
    long timestamp;

    SensorData(double ws = 0, double temp = 0, double hum = 0, long time = 0)
        : windspeed(ws), temperature(temp), humidity(hum), timestamp(time) {}
};

#endif