#include "dataCollector.hpp"
#include <mutex>
#include <iostream>

DataCollector::DataCollector()
{

}

/** Makes sure the code is ready to run if you call the method getSensorData */
void DataCollector::setDataReady(bool ready) {
    std::lock_guard<std::mutex> lock(m_mtx);
    this->m_dataReady = ready;
    if (ready) {
        m_dataReadySignal.notify_all();
    }
}

/** Inserts sensor data into a sensor using the sensors id. */
void DataCollector::addData(unsigned int sensorId, SensorData data)
{
    if (!this->m_sensorData.contains(sensorId))
    {
        this->m_sensorData[sensorId] = {};
    }
    this->m_sensorData[sensorId].push(data);
    this->m_dataReady = true;
}

/**
 * @returns a pointer to data from a specified sensor or `nullptr` if no data exists. 
 */
const std::queue<SensorData> *DataCollector::getSensorData(unsigned int sensorId) noexcept
{
    std::unique_lock<std::mutex> lock(m_mtx);
    if (m_sensorData.size() == 0)
    {
        this->m_dataReadySignal.wait(lock);
    }
    if (this->m_sensorData.contains(sensorId))
        return &this->m_sensorData.at(sensorId);
    else 
        return nullptr;
}

/**
 * @returns a map with all sensors data that is currently stored in the class.
 */
const std::map<unsigned int, std::queue<SensorData>> &DataCollector::getSensorData() noexcept
{
    return this->m_sensorData;
}

// /**
//  * Method removes the returned sensor data from queue when called.   
//  * @returns pointer to sensor data or nullptr if sensor does not exist
//  */
// std::shared_ptr<SensorData> DataCollector::queryData(unsigned int sensorId)
// {
//     std::unique_lock<std::mutex> lock_guard(m_mtx);
//     this->m_dataReadySignal.wait(lock_guard);

//     if (!this->m_sensorData.contains(sensorId) || this->m_sensorData.at(sensorId).size() == 0)
//         return nullptr;

//     std::shared_ptr<SensorData> ptr;
//     SensorData data = this->m_sensorData[sensorId].front();
//     ptr = std::make_shared<SensorData>(data);

//     this->m_sensorData[sensorId].pop();
//     return ptr;
// }
