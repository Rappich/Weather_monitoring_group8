#include "dataStatistics.hpp"
#include <limits>

// Konstruktor
DataStatistics::DataStatistics() : avg(0), min(std::numeric_limits<double>::max()), max(std::numeric_limits<double>::lowest()) {}

// Beräkna alla statistikvärden
void DataStatistics::calculateAll(std::queue<SensorData>& data) {
    calculateMin(data);
    calculateAvg(data);
    calculateMax(data);
}

// Beräkna minvärdet
void DataStatistics::calculateMin(std::queue<SensorData>& data) {
    min = std::numeric_limits<double>::max();
    std::queue<SensorData> temp = data;
    while (!temp.empty()) {
        SensorData sd = temp.front();
        temp.pop();
        if (sd.temperature < min) min = sd.temperature;
        if (sd.humidity < min) min = sd.humidity;
        if (sd.windSpeed < min) min = sd.windSpeed;
    }
}

// Beräkna medelvärdet
void DataStatistics::calculateAvg(std::queue<SensorData>& data) {
    double sum = 0;
    int count = 0;
    std::queue<SensorData> temp = data;
    while (!temp.empty()) {
        SensorData sd = temp.front();
        temp.pop();
        sum += sd.temperature + sd.humidity + sd.windSpeed;
        count += 3; // Tre värden per SensorData
    }
    avg = (count != 0) ? sum / count : 0;
}

// Beräkna maxvärdet
void DataStatistics::calculateMax(std::queue<SensorData>& data) {
    max = std::numeric_limits<double>::lowest();
    std::queue<SensorData> temp = data;
    while (!temp.empty()) {
        SensorData sd = temp.front();
        temp.pop();
        if (sd.temperature > max) max = sd.temperature;
        if (sd.humidity > max) max = sd.humidity;
        if (sd.windSpeed > max) max = sd.windSpeed;
    }
}

// Getter-metoder
double DataStatistics::getAvg() const {
    return avg;
}

double DataStatistics::getMin() const {
    return min;
}

double DataStatistics::getMax() const {
    return max;
}
