#include "sensorManager.hpp"
#include <thread>
#include <exception>

SensorManager::SensorManager() 
{
    this->isRunning = true;

    this->m_thread = std::make_shared<std::thread>(std::thread([this]()
    {
        short readings = 0;
        while(this->isRunning)
        {
            {
                std::lock_guard<std::mutex> lock(this->m_mtx);

                for (auto& pair : sensors)
                {
                    pair.second.readData();
                    this->m_dataCollector.addData(pair.first, pair.second.getData());
                }

                if (++readings >= 10)
                {
                    this->m_dataCollector.setDataReady(true);
                    readings = 0;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }));
}

SensorManager::~SensorManager()
{

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

Sensor &SensorManager::getSensor(unsigned int id)
{
    std::unique_lock<std::mutex> guard(m_mtx);
    if (id >= sensors.size()) throw std::exception();
    return sensors.at(id);
}

void SensorManager::setSensor(unsigned int id, Sensor &sensor)
{
    std::lock_guard<std::mutex> guard(m_mtx);
    sensors.insert({id, sensor});
    std::cout << "Sensor with ID " << id << " has been updated.\n";
}

void SensorManager::stopReading()
{
    // std::lock_guard<std::mutex> lock_guard(this->m_mtx);
    this->isRunning = false;
    if (this->m_thread->joinable())
        this->m_thread->join();
}

DataCollector *SensorManager::getDataCollector()
{
    return &this->m_dataCollector;
}
