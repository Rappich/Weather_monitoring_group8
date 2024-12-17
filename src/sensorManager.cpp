#include "sensorManager.hpp"
#include <thread>

SensorManager::SensorManager() 
{
    this->isRunning = true;

    this->m_thread = new std::thread([this]()
    {
        short readings = 0;
        while(this->isRunning)
        {
            this->m_mtx.lock();
            for (auto& pair : sensors)
            {
                pair.second.readData();
                this->m_dataCollector.addData(pair.second.getID(), pair.second.getData());
            }
            this->m_mtx.unlock();

            if (++readings >= 10)
            {
                std::cout << readings << std::endl;
                this->m_dataCollector.setDataReady(true);
                readings = 0;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    this->m_thread->detach();
}

SensorManager::~SensorManager()
{
    this->isRunning = false;
    this->m_thread->join();
    delete this->m_thread;
    this->m_thread = nullptr;
}

// Generates a specified number of sensors
void SensorManager::generate(unsigned int numSensors)
{
    {
        std::lock_guard<std::mutex> lock_guard(m_mtx);

        for (unsigned int i = 0; i < numSensors; ++i)
        {
            sensors.insert({i, Sensor(i)});
        } //lämnar scope
    }
    std::cout << numSensors << " sensors initialized.\n";
}

Sensor &SensorManager::getSensor(int id)
{
    std::lock_guard<std::mutex> lock_guard(m_mtx);
    return sensors.at(id);
}

void SensorManager::setSensor(unsigned int id, Sensor &sensor)
{
    std::lock_guard<std::mutex> lock_guard(m_mtx);
    sensors.insert({id, sensor});
    std::cout << "Sensor with ID " << id << " has been updated.\n";
}

void SensorManager::stopReading()
{
    this->isRunning = false;
}

DataCollector *SensorManager::getDataCollector()
{
    return &this->m_dataCollector;
}
