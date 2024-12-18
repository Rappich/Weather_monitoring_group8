#ifndef GLOBALS_PRINT_HPP
#define GLOBALS_PRINT_HPP

#include <vector>
#include <memory>

class SensorManager;

using Cities = std::vector<std::pair<std::string, std::shared_ptr<SensorManager>>>;

void displayMenu();
void showSensorData(Cities &cities);
void createCity(Cities &cities);
void modifyCity(Cities &cities);
void removeCity(Cities &cities);
void printCities(Cities &cities);

#endif