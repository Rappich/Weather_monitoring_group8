#include "dataCollector.hpp"

DataCollector::DataCollector()
{

}

void DataCollector::resetFlag()
{
    this->dataReady = false;
}

void DataCollector::setDataReady(bool ready)
{
    this->dataReady = ready;
}

void DataCollector::addData(int sensorId, SensorData data)
{
    this->m_sensorData[sensorId].push(data);
}

const std::queue<SensorData> *DataCollector::getSensorData(int sensorId) const noexcept
{
    if (this->m_sensorData.contains(sensorId))
        return &this->m_sensorData.at(sensorId);
    else 
        return nullptr;
}

const std::map<int, std::queue<SensorData>> DataCollector::getSensorData() const noexcept
{
    return this->m_sensorData;
}
