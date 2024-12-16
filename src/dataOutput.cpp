#include "../include/DataOutput.hpp"
#include <iostream>


void DataOutput::displayStatistics() {
    // Print the statistics using DataStatistics
    std::cout << "Displaying statistics..." << std::endl;
    std::cout << "Average temperature: " << dataStatistics.getAverageTemperature() << std::endl;
    std::cout << "Average humidity: " << dataStatistics.getAverageHumidity() << std::endl;
    std::cout << "Avrige windspeed" << dataStatistics.getAverageWindspeed() << std::endl;
}

void DataOutput::displayAvailableData() {
    // Print the current using DataStatistics
    std::cout << "Displaying current data..." << std::endl;
    std::cout << "Temperature: " << dataCollector.getTemperature() << std::endl;
    std::cout << "Humidity: " << dataCollector.getHumidity() << std::endl;
    std::cout << "Windspeed: " << dataCollector.getWindspeed() << std::endl;
}
