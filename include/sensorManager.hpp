#ifndef SENSORMANAGER_HPP
#define SENSORMANAGER_HPP

#include "sensor.hpp"
#include "dataCollector.hpp"
#include <map>
#include <atomic>
#include <iostream>
#include <thread>

class SensorManager
{
private:
    // map of sensor IDs to Sensor objects
    std::map<unsigned int, Sensor> sensors;
    
    std::mutex m_mtx, m_threadmtx;
    std::atomic_bool isRunning;

    DataCollector m_dataCollector;

    std::shared_ptr<std::thread> m_thread{nullptr};

    std::condition_variable m_stopSignal;
public:
    SensorManager();
    virtual ~SensorManager();

    // generates and initializes sensors
    void generate(unsigned int numSensors);

    // retrieves a sensor by ID from sensor class
    Sensor &getSensor(unsigned int id);

    // add a sensor to the hashmap
    void setSensor(unsigned int, Sensor &);

    void stopReading();

    DataCollector *getDataCollector();
};

#endif