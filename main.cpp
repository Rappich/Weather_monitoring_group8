#include <iostream>
#include <map>
#include <signal.h>
#include "include/dataBase.hpp"
#include "include/dataCollector.hpp"
#include "include/dataStatistics.hpp"
#include "include/lifetimeStatistics.hpp"
#include "include/measurementData.hpp"
#include "include/sensor.hpp"
#include "include/sensorData.hpp"
#include "include/sensorManager.hpp"

//function that simulates data readData()

// void handleSIGINT(int signal)
// {
//     std::cout << signal << ": has been caught" << std::endl;
// }

int main(int argc, char const *argv[])
{
    std::cout << "Welcome stranger" << std::endl;
    std::cout << "To check weather please select a city" << std::endl;
    
    
    std::vector<std::pair<std::string, std::shared_ptr<SensorManager>>> city = {};
    city.emplace_back("Skellefteå", std::make_shared<SensorManager>());
    city.emplace_back("Stockholm", std::make_shared<SensorManager>());
    city.emplace_back("Helsingborg", std::make_shared<SensorManager>());

    // signal(SIGINT, handleSIGINT);
    int choice;

    do
    {        
        std::cout << "0: Exit" << std::endl;
        for (int i = 0; i < city.size(); i++)
        {
            std::cout << i + 1 << ": " << city[i].first << std::endl;
        }

        std::cin >> choice;

        if (choice<0)
        {
            std::cout<< "Invalid choice. Please try again."<<std::endl; 
            continue;
        }


        else if(choice>0)
        {
        switch (choice)
        {
            case 1: {
                std::cout << "You selected Skellefteå" << std::endl;
                SensorManager &sensors = *city[choice].second.get();
                DataCollector *collector = sensors.getDataCollector();

                DataStatistics statistics{};

                std::cout << collector->getSensorData().size() << std::endl;
                for (const auto &sensor : collector->getSensorData())
                {
                    statistics.calculateAll(collector->getSensorData(sensor.first));
                    statistics.displayStatistics();
                }
                
                break;
            }
            case 2:
                std::cout << "You selected Helsignborg" << std::endl;
                break;

            case 3:
                std::cout << "You selected Stockholm" << std::endl;
                break;
            
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
            }
        }
    }
    while(choice!=0);
    // Display current and historical data.
    return 0;
}
