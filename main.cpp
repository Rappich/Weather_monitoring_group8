#include "globals.hpp"

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
        std::cout << "Enter selection: ";
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

