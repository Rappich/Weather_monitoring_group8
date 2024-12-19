#include "globals.hpp"

#include "dataCollector.hpp"
#include "dataStatistics.hpp"
#include <vector>
#include <csignal>
#include <iostream>

#define NO_COLOR "\e[0m"
#define LIST_COLOR_NUMBERS "\e[1;30m"
#define LIST_COLOR_BOLD "\e[1m"
#define TITLE_COLOR "\e[1;32m"


// Display menu for programs functionality
void displayMenu()
{
    std::cout << TITLE_COLOR << "Menu: \n" << NO_COLOR;
    std::cout << LIST_COLOR_NUMBERS << "1. " << NO_COLOR << "Show Sensor Data \n";
    std::cout << LIST_COLOR_NUMBERS << "2. " << NO_COLOR << "Create City \n";
    std::cout << LIST_COLOR_NUMBERS << "3. " << NO_COLOR << "Modify City \n";
    std::cout << LIST_COLOR_NUMBERS << "4. " << NO_COLOR << "Remove City \n";
    std::cout << LIST_COLOR_NUMBERS << "0. " << NO_COLOR << "Exit \n";
}

// Show sensor data in real time from chosen city
void showSensorData(Cities &cities)
{
    if (cities.empty())
    {
        std::cout << "No cities available.\n";
        return;
    }

    std::cout << "Select a city to view its sensor data:\n";
    for (size_t i = 0; i < cities.size(); ++i)
    {
        std::cout << i + 1 << ". " << cities[i].first << "\n";
    }

    int choice;
    std::cout << "Please enter selection: ";
    std::cin >> choice;

    if (choice < 1 || choice > cities.size())
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    SensorManager &sensorManager = *cities[choice - 1].second;
    DataCollector *dataCollector = sensorManager.getDataCollector();

    if (dataCollector == nullptr)
    {
        std::cerr << "Data collector is null.\n";
        return;
    }

    std::cout << "Displaying real-time sensor data for " << cities[choice - 1].first << ":\n";
    sensorManager.generate(1);

    DataStatistics statistics;
    
    std::atomic_bool isRunning = true;
    std::condition_variable signalDone;

    std::mutex mtx1, mtx2;

    auto &dataMap = dataCollector->getSensorData();

    std::thread t1 {[&]() {                
        while (isRunning)
        {
            std::unique_lock<std::mutex> lock(mtx1);
            for (const auto &[sensorId, sensorQueue] : dataMap)
            {
                std::cout << TITLE_COLOR << "\nSensor ID: " << NO_COLOR << sensorId << "\n";
                statistics.print(sensorQueue.back());                
            }                
            signalDone.wait_for(lock, std::chrono::seconds(2));
        }
    }};

    std::thread t2 {[&]() {
        std::unique_lock<std::mutex> lock(mtx2);

        signalDone.wait(lock);
        for (auto &[sensorId, sensorQueue] : dataMap)
        {
            statistics.calculateAll(&sensorQueue);
            std::cout << TITLE_COLOR << "\nSummary for sensor with ID: " << NO_COLOR << sensorId << "\n";
            statistics.displayStatistics();
        }
    }};

    std::cout << "Press Enter to stop displaying data...\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    signalDone.notify_all();
    isRunning = false;

    sensorManager.stopReading();
    
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();   
}

// Adds a city with avg readings
void createCity(Cities &cities)
{
    std::string name;
    double avgTemperature, avgHumidity, avgWind;

    std::cout << "Enter the name of the city: ";
    std::cin.ignore(); 
    std::getline(std::cin, name);

    std::cout << "Enter the average temperature for " << name << " (°C): ";
    std::cin >> avgTemperature;

    std::cout << "Enter the average humidity for " << name << " (%): ";
    std::cin >> avgHumidity;

    std::cout << "Enter the average wind speed for " << name << " (m/s): ";
    std::cin >> avgWind;

    if (std::cin.fail() || avgTemperature < GLOBAL_MIN_TEMPERATURE || avgTemperature > GLOBAL_MAX_TEMPERATURE ||
        avgHumidity < GLOBAL_MIN_HUMIDITY || avgHumidity > GLOBAL_MAX_HUMIDITY || avgWind < GLOBAL_MIN_WIND || avgWind > GLOBAL_MAX_WIND)
    {
        std::cout << "Invalid input. Please ensure all values are within the expected ranges:\n"
                  << "- Temperature: -40°C to 40°C\n"
                  << "- Humidity: 0% to 100%\n"
                  << "- Wind Speed: 0 m/s to 30 m/s\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    auto sensorManager = std::make_shared<SensorManager>(avgTemperature, avgHumidity, avgWind);
    sensorManager->generate(1); 

    SensorData sensorData(avgWind, avgTemperature, avgHumidity, std::time(nullptr));
    sensorManager->getDataCollector()->addData(1, sensorData);

    cities.push_back({name, sensorManager});

    std::cout << "City \"" << name << "\" has been created with the following average conditions:\n"
              << "- Average Temperature: " << avgTemperature << "°C\n"
              << "- Average Humidity: " << avgHumidity << "%\n"
              << "- Average Wind Speed: " << avgWind << " m/s\n";
}

// Function to modify existing cities
void modifyCity(Cities &cities)
{
    if (cities.empty())
    {
        std::cout << "No cities available to modify.\n";
        return;
    }

    std::cout << "Select a city to modify:\n";
    for (size_t i = 0; i < cities.size(); ++i)
    {
        std::cout << i + 1 << ". " << cities[i].first << "\n";
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > cities.size())
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    std::cout << "Enter the new name for " << cities[choice - 1].first << ": ";
    std::string newName;
    std::cin.ignore();
    std::getline(std::cin, newName);

    double newAvgTemp, newAvgHumidity, newAvgWind;
    std::cout << "Enter the new average temperature (°C): ";
    std::cin >> newAvgTemp;
    std::cout << "Enter the new average humidity (%): ";
    std::cin >> newAvgHumidity;
    std::cout << "Enter the new average wind speed (m/s): ";
    std::cin >> newAvgWind;

    if (std::cin.fail() || newAvgTemp < GLOBAL_MIN_TEMPERATURE || newAvgTemp > GLOBAL_MAX_TEMPERATURE ||
        newAvgHumidity < GLOBAL_MIN_HUMIDITY || newAvgHumidity > GLOBAL_MAX_HUMIDITY ||
        newAvgWind < GLOBAL_MIN_WIND || newAvgWind > GLOBAL_MAX_WIND)
    {
        std::cout << "Invalid input. Please ensure all values are within valid ranges.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    cities[choice - 1].first = newName;

    SensorManager &sensorManager = *cities[choice - 1].second;
    Sensor &sensor = sensorManager.getSensor(0);
    SensorData newSensorData = sensor.generateData(newAvgTemp, newAvgHumidity, newAvgWind);
    sensorManager.getDataCollector()->addData(1, newSensorData);

    std::cout << "City updated successfully!\n";
    std::cout << "New name: " << newName << "\n";
    std::cout << "New average temperature: " << newAvgTemp << "°C\n";
    std::cout << "New average humidity: " << newAvgHumidity << "%\n";
    std::cout << "New average wind speed: " << newAvgWind << " m/s\n";
}

//Function to remove city from program 
void removeCity(Cities &cities)
{
    if (cities.empty())
    {
        std::cout << "No cities available to remove.\n";
        return;
    }

    std::cout << "Select a city to remove:\n";
    for (size_t i = 0; i < cities.size(); ++i)
    {
        std::cout << i + 1 << ". " << cities[i].first << "\n";
    }

    int choice;
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > cities.size())
    {
        std::cout << "Invalid choice. Please enter a number between 1 and " << cities.size() << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    std::string removedCity = cities[choice - 1].first;
    cities.erase(cities.begin() + (choice - 1));

    std::cout << "City \"" << removedCity << "\" has been removed successfully.\n";
}
