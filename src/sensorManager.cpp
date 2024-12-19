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
            std::unique_lock<std::mutex> threadLock(this->m_threadmtx);
            {
                std::lock_guard<std::mutex> lock(this->m_mtx);

                for (auto& pair : sensors)
                {
                    pair.second.readData();
                    this->m_dataCollector.addData(pair.first, pair.second.getData());
                }

                this->getDataCollector()->setDataReady(true);
            }

            this->m_stopSignal.wait_for(threadLock, std::chrono::milliseconds(500));
        }
    }));
}

SensorManager::SensorManager(double avgTemp, double avgHumidity, double avgWindspeed)
    : avgTemp(avgTemp), avgHumidity(avgHumidity), avgWindspeed(avgWindspeed)
{
    this->isRunning = true;

    this->m_thread = std::make_shared<std::thread>(std::thread([this]()
    {
        short readings = 0;
        while(this->isRunning)
        {
            std::unique_lock<std::mutex> threadLock(this->m_threadmtx);
            {
                std::lock_guard<std::mutex> lock(this->m_mtx);

                for (auto& pair : sensors)
                {
                    this->m_dataCollector.addData(pair.first, pair.second.generateData(this->avgTemp, this->avgHumidity, this->avgWindspeed));
                }

                this->getDataCollector()->setDataReady(true);
            }

            this->m_stopSignal.wait_for(threadLock, std::chrono::milliseconds(500));
        }
    }));
}


SensorManager::~SensorManager()
{
    stopReading();
}

// Generates a specified number of sensors
void SensorManager::generate(unsigned int numSensors)
{
    {
        std::lock_guard<std::mutex> lock_guard(m_mtx);

        for (unsigned int i = 0; i < numSensors; i++)
        {
            sensors.insert({i + 1, Sensor(i)});
        }
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


//Instructs sensor thread to stop reading
void SensorManager::stopReading()
{
    std::lock_guard<std::mutex> lock_guard(this->m_mtx);
    this->isRunning = false;
    m_stopSignal.notify_all();
    if (this->m_thread->joinable())
        this->m_thread->join();
}

DataCollector *SensorManager::getDataCollector()
{
    return &this->m_dataCollector;
}
