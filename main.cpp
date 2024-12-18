#include "include/dataCollector.hpp"
#include "include/dataStatistics.hpp"
#include "include/sensorManager.hpp"

//function that simulates data readData()

// void handleSIGINT(int signal)
// {
//     std::cout << signal << ": has been caught" << std::endl;
// }

// class ShouldQuit
// {
//     virtual ~ShouldQuit() = 0;
//     static std::atomic_bool shouldQuit;
// public:
//     static void handleQuit(int signal)
//     {
//         ShouldQuit::shouldQuit = true;
//     }

//     static std::atomic_bool &shouldQuit()
//     {
//         return ShouldQuit::shouldQuit;
//     }
// };

int main(int argc, char const *argv[])
{
    std::cout << "Welcome stranger" << std::endl;
    std::cout << "To check weather please select a city" << std::endl;
        
    std::vector<std::pair<std::string, std::shared_ptr<SensorManager>>> city = {};
    city.push_back({"Skellefteå", std::make_shared<SensorManager>()});
    city.push_back({"Stockholm", std::make_shared<SensorManager>()});
    city.push_back({"Helsingborg", std::make_shared<SensorManager>()});

    // signal(SIGINT, ShouldQuit::handleQuit);
    // signal(SIGKILL, ShouldQuit::handleQuit);

    int choice;

    do
    {        
        std::cout << "0: Exit" << std::endl;
        for (int i = 0; i < city.size(); i++)
        {
            std::cout << i + 1 << ": " << city[i].first << std::endl;
        }

        input: 
        if ((std::cin >> choice))
        {
            goto input;
        }

        if (choice<0)
        {
            std::cout<< "Invalid choice. Please try again."<<std::endl; 
            continue;
        }


        else if(choice > 0 && choice <= city.size() + 1)
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

                SensorManager &sensors = *city[choice].second.get();
                DataCollector *collector = sensors.getDataCollector();

                sensors.generate(1);

                DataStatistics statistics{};

                std::atomic_bool shouldQuit = false;
                auto &data = collector->getSensorData();

                std::thread t1([&statistics, &collector, choice, &shouldQuit]() {
                    while (!shouldQuit)
                    {
                        for (int i = 0; i < collector->getSensorData().size(); i++)
                        {
                            std::cout << "---- Live sensor " << i + 1 << " ----" << std::endl;
                            SensorData data = collector->getSensorData(i + 1)->back();
                            statistics.print(data); //kontinuerlig print av realdata
                        }
                        
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    }
                });

                std::thread t2([&statistics, &collector, choice, &shouldQuit]() {
                    while (!shouldQuit)
                    {
                        //här låg displayStatistics                        
                        std::this_thread::sleep_for(std::chrono::seconds(5));
                    }
                    
                    statistics.calculateAll(collector->getSensorData(choice));
                    statistics.displayStatistics(); //nu ligger den här
                });
                
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                // std::cin.get();

                std::this_thread::sleep_for(std::chrono::seconds(10));
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
