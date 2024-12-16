#ifndef DATASTATISTICS_HPP
#define DATASTATISTICS_HPP
#include <queue>
#include "sensorData.hpp"
class DataStatistics
{
private:
double avg, min, max;

public:
DataStatistics();

void calculateAll(std::queue<SensorData>& data); 
void calculateMin(std::queue<SensorData>& data); 
void calculateAvg(std::queue<SensorData>& data); 
void calculateMax(std::queue<SensorData>& data); 

double getAvg() const; 
double getMin() const; 
double getMax() const;
    
};






#endif