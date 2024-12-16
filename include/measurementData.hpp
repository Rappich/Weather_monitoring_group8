#ifndef MEASURMENTDATA_HPP
#define MEASURMENTDATA_HPP

struct MeasurementData
{
    double min;
    double max;
    double avg;

    MeasurementData(double avg = 0.0, double max = 0.0, double min = 0.0)
        : avg(avg), max(max), min(min) {}
};
#endif