#ifndef DATAOUTPUT_HPP
#define DATAOUTPUT_HPP

#include "DataStatistics.hpp"
#include "DataCollector.hpp"

class DataOutput
{

private:
    DataStatistics dataStatistics;
    DataCollector dataCollector;

public:
    void displayStatistics();
    void displayAvailableData();
};

#endif
