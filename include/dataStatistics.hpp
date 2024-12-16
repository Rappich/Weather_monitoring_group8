#ifndef DATASTATISTICS.HPP
#define DATASTATISTICS.HPP
#include <queue>
#include "sensorData.hpp"
class dataStatistics
{
private:
double avg, min, max;

public:
dataStatistics(const double avg, double min, double max);

void calculateAll(std::queue<SensorData>& data); 
void calculateMin(std::queue<SensorData>& data); 
void calculateAvg(std::queue<SensorData>& data); 
void calculateMax(std::queue<SensorData>& data); 

double getAvg() const; 
double getMin() const; 
double getMax() const;
    
};






#endif