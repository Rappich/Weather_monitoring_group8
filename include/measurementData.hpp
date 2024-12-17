#ifndef MEASURMENTDATA_HPP
#define MEASURMENTDATA_HPP

struct MeasurementData
{
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();
    double avg = 0;
};
#endif