#include "include/dataCollector.hpp"
#include "include/dataStatistics.hpp"
#include "include/sensorManager.hpp"
#include <vector>

using Cities = std::vector<std::pair<std::string, std::shared_ptr<SensorManager>>>;

void displayMenu();
void showSensorData(Cities &cities);
void createCity(Cities &cities);
void modifyCity(Cities &cities);
void removeCity(Cities &cities);
void printCities(Cities &cities);

int main()
{

    // loadProgram(); här skulle vi kunna ha en funktion som laddar allt från en databas.

    Cities cities = {};
    cities.push_back({"Skellefteå", std::make_shared<SensorManager>()});
    cities.push_back({"Stockholm", std::make_shared<SensorManager>()});
    cities.push_back({"Helsingborg", std::make_shared<SensorManager>()});
    bool running = true;

    while (running)

    {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input. Please try again\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            showSensorData(cities);
            break;
        }
        case 2:
        {
            createCity(cities);
            break;
        }
        case 3:
        {
            modifyCity(cities);
            break;
        }
        case 4:
        {
            removeCity(cities);
            break;
        }
        case 0:
        {
            running = false;
            std::cout << "Exiting program.\n"; // här kan vi lägga till en spara funktion sen
            break;
        }
        }
    }

    return 0;
}

void displayMenu()
{
    std::cout << "Menu: \n";
    std::cout << "1. Show Sensor Data \n";
    std::cout << "2. Create City \n";
    std::cout << "3. Modify City \n";
    std::cout << "4. Remove City \n";
    std::cout << "0. Exit \n";
}

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
    std::cin >> choice;

    if (choice < 1 || choice > cities.size())
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    SensorManager &sensorManager = *cities[choice - 1].second;
    DataCollector *dataCollector = sensorManager.getDataCollector();

    std::cout << "Displaying real-time sensor data for " << cities[choice - 1].first << ":\n";
    sensorManager.generate(3);

    DataStatistics statistics;

    auto &dataMap = dataCollector->getSensorData();
    for (const auto &[sensorId, sensorQueue] : dataMap)
    {
        std::cout << "\nSensor ID: " << sensorId << "\n";
        statistics.calculateAll(&sensorQueue);
        statistics.displayStatistics();
    }

    sensorManager.stopReading();
}

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

    auto sensorManager = std::make_shared<SensorManager>();
    sensorManager->generate(1); 

    SensorData sensorData(avgWind, avgTemperature, avgHumidity, std::time(nullptr));
    sensorManager->getDataCollector()->addData(1, sensorData);

    cities.push_back({name, sensorManager});

    std::cout << "City \"" << name << "\" has been created with the following average conditions:\n"
              << "- Average Temperature: " << avgTemperature << "°C\n"
              << "- Average Humidity: " << avgHumidity << "%\n"
              << "- Average Wind Speed: " << avgWind << " m/s\n";
}

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
