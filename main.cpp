#include "include/dataCollector.hpp"
#include "include/dataStatistics.hpp"
#include "include/sensorManager.hpp"

/**
 * 1. Visa mätvärden för stad
 *      -> 1. Visa lista på städer
 *      -> 2. Stadens id
 * 1. Skapa stad
 *      -> 1. Namn på stad
 *      -> 2. Medel temp (dev)
 *      -> 3. Medel fuktighet (dev)
 *      -> 4. Medel vind (dev)
 * 2. Modifiera stad
 *      -> 1. Stadens id
 *      -> 2. Namn på stad
 *      -> 3. Medel temp (dev)
 *      -> 4. Medel fuktighet (dev)
 *      -> 5. Medel vind (dev)
 * 3. Ta bort stad
 *      -> 1. Stadens id
 * 4. Avsluta
 * 
 */

using Cities = std::vector<std::pair<std::string, std::shared_ptr<SensorManager>>>;

void showSensorData(Cities& cities);
void createCity(Cities& cities);
void modifyCity(Cities& cities);
void removeCity(Cities& cities);
void printCities(Cities& cities);

int main(int argc, char const *argv[])
{
    std::cout << "Welcome stranger" << std::endl;
    std::cout << "To check weather please select a city" << std::endl;

    std::vector<std::pair<std::string, void(*)(Cities &cities)>> menu;
        
    Cities cities = {};
    cities.emplace_back("Skellefteå", std::make_shared<SensorManager>());
    cities.emplace_back("Stockholm", std::make_shared<SensorManager>());
    cities.emplace_back("Helsingborg", std::make_shared<SensorManager>());

    int choice;

    do
    {        
        std::cout << "0: Exit" << std::endl;
        for (int i = 0; i < cities.size(); i++)
        {
            std::cout << i + 1 << ": " << cities[i].first << std::endl;
        }
        
    input:
        choice = 0; 
        if (!(std::cin >> choice))
        {
            goto input;
        }

        if (choice<0)
        {
            std::cout<< "Invalid choice. Please try again." << std::endl; 
            continue;
        }


        else if(choice > 0 && choice <= cities.size() + 1)
        {
            switch (choice)
            {
                case 1: {
                    std::cout << "You selected Skellefteå" << std::endl;
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

                // #ifdef WINDOWS
                //     system("cls");
                // #else
                //     system("clear");
                // #endif

                SensorManager &sensors = *cities[choice].second.get();
                DataCollector *collector = sensors.getDataCollector();

                sensors.generate(1);

                DataStatistics statistics{};

                std::atomic_bool shouldQuit = false;
                auto &data = collector->getSensorData();

                std::condition_variable signalDone;
                std::mutex threadMtx1, threadMtx2;

                std::thread t1([&statistics, &collector, choice, &shouldQuit, &threadMtx1, &signalDone]() {
                    while (!shouldQuit)
                    {   
                        std::unique_lock<std::mutex> lock(threadMtx1);
                        for (int i = 0; i < collector->getSensorData().size(); i++)
                        {
                            std::cout << "---- Live sensor " << i + 1 << " ----" << std::endl;
                            SensorData data = collector->getSensorData(i + 1)->back();
                            statistics.print(data); //kontinuerlig print av realdata
                        }
                        
                        signalDone.wait_for(lock, std::chrono::seconds(2));
                    }
                });

                std::thread t2([&statistics, &collector, choice, &shouldQuit, &threadMtx2, &signalDone]() {
                    std::unique_lock<std::mutex> lock(threadMtx2);
                    while (!shouldQuit)
                    {
                        //här låg displayStatistics                        
                        signalDone.wait_for(lock, std::chrono::seconds(5));
                    }
                    
                    statistics.calculateAll(collector->getSensorData(choice));
                    statistics.displayStatistics(); //nu ligger den här
                });

                std::this_thread::sleep_for(std::chrono::seconds(10));
                signalDone.notify_all();
                shouldQuit = true;

                sensors.stopReading();
                
                if (t1.joinable()) t1.join();
                if (t2.joinable()) t2.join();

            }
                
        }
    while(choice != 0);

    std::cout << "Exiting..." << std::endl;
    // Display current and historical data.
    return 0;
}

void showSensorData(Cities& cities)
{

}

void createCity(Cities& cities)
{

}

void modifyCity(Cities& cities)
{

}

void removeCity(Cities& cities)
{

}
