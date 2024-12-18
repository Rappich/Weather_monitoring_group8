#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>
#include <string>
#include <vector>

#include "dataStatistics.hpp"
#include "sensorData.hpp"

class Database
{
public:
    // bool createCity(std::string name);
    // bool removeCity(int index);
    // bool modifyCity(int index);
    // std::vector<SensorData> loadSensorData(int sensorId);
    // DataStatistics loadStatistics(int sensorId);

    // bool saveStatistics(int sensorId);
    // bool saveSensorData(std::vector<SensorData> data);
private:
    sqlite3 *m_db;
};

#endif