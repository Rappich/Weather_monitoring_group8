#ifndef DATAOUTPUT_HPP
#define DATAOUTPUT_HPP

#include "dataStatistics.hpp"
#include "dataCollector.hpp"

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
