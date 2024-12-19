#include "dataStatistics.hpp"
#include <limits>
#include "measurementData.hpp"
#include <iostream>

DataStatistics::DataStatistics() {}

// Summarizes sensor data from the parameter
void DataStatistics::calculateAll(const std::queue<SensorData> *data)
{
    if (data == nullptr) 
    {
        std::cerr << "Data is null" << std::endl;
        return;
    }

    if (data->empty())
    {
        return;
    }

    auto first = data->front();

    temperature.avg = 0;
    windspeed.avg = 0;
    humidity.avg = 0;

    temperature.max = first.temperature;
    windspeed.max = first.windspeed;
    humidity.max = first.humidity;

    temperature.min = first.temperature;
    windspeed.min = first.windspeed;
    humidity.min = first.humidity;

    int count = 0;

    std::queue<SensorData> tempQueue = *data;

    while (!tempQueue.empty())
    {
        auto &data = tempQueue.front();

        if (data.temperature < temperature.min)
            temperature.min = data.temperature;
        
        if (data.temperature >= temperature.max)
            temperature.max = data.temperature;

        if (data.humidity < humidity.min)
            humidity.min = data.humidity;
        
        if (data.humidity >= humidity.max)
            humidity.max = data.humidity;

        if (data.windspeed < windspeed.min)
            windspeed.min = data.windspeed;
        
        if (data.windspeed >= windspeed.max)
            windspeed.max = data.windspeed;

        windspeed.avg += data.windspeed;
        temperature.avg += data.temperature;
        humidity.avg += data.humidity;

        tempQueue.pop();
        ++count;
    }

    temperature.avg /= (double) count;
    windspeed.avg /= (double) count;
    humidity.avg /= (double) count;
}

/**
 * @returns Returns the windspeed
  */

const MeasurementData DataStatistics::getWindspeed() const noexcept
{
    return windspeed;
}

/**
 * @returns Returns the temperature
  */
const MeasurementData DataStatistics::getTemperature() const noexcept
{
    return temperature;
}

/**
 * @returns Returns the humidity
  */
const MeasurementData DataStatistics::getHumidity() const noexcept
{
    return humidity;
}

 // Prints the avarage temperature, humidity and windspeed from simulated real-time data
void DataStatistics::displayStatistics()
{
    std::cout <<"\033[1;31mDisplaying statistics:\033[0m" << std::endl;
    std::cout <<"Average temperature: " << temperature.avg << std::endl;
    std::cout <<"Lowest measured tempreature: " << temperature.min <<std::endl; 
    std::cout <<"Highest measured tempreature: " << temperature.max <<std::endl; 

    std::cout <<"Average humidity: " << humidity.avg << std::endl;
    std::cout <<"Lowest humidity: " << humidity.min <<std::endl; 
    std::cout <<"Highest humidity: " << humidity.max <<std::endl; 
    
    std::cout <<"Avarege windspeed: " << windspeed.avg << std::endl;
    std::cout <<"Lowest windspeed: " << windspeed.min <<std::endl; 
    std::cout <<"Highest windspeed: " << windspeed.max <<std::endl; 
}


// Prints the simulated real time data
void DataStatistics::print(const SensorData &data)
{
    std::cout << "Temperature: " << data.temperature << std::endl;
    std::cout << "Humidity: " << data.humidity << std::endl;
    std::cout << "Windspeed: " << data.windspeed << std::endl;
}


/* void DataStatistics::displayAvailableData()
{
    //
    std::cout << "Displaying last measured data..." << std::endl;
   // std::cout << "Temperature: " << dataCollector.getTemperature() << std::endl;
   // std::cout << "Humidity: " << dataCollector.getHumidity() << std::endl;
    std::cout << "Windspeed: " << dataCollector.getWindspeed() << std::endl;
} */