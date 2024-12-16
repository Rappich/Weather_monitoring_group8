#include "dataCollector.hpp"

DataCollector::DataCollector()
{

}

/** Tells the class that the data is not ready to be summarized */
void DataCollector::resetFlag()
{
    this->dataReady = false;
}

/** If true the class values will be emptied later. */
void DataCollector::setDataReady(bool ready)
{
    this->dataReady = ready;
}

/** Inserts sensor data into a sensor using the sensors id. */
void DataCollector::addData(unsigned int sensorId, SensorData data)
{
    this->m_sensorData[sensorId].push(data);
}

/**
 * @returns a pointer to data from a specified sensor or `nullptr` if no data exists. 
 */
const std::queue<SensorData> *DataCollector::getSensorData(unsigned int sensorId) const noexcept
{
    if (this->m_sensorData.contains(sensorId))
        return &this->m_sensorData.at(sensorId);
    else 
        return nullptr;
}

/**
 * @returns a map with all sensors data that is currently stored in the class.
 */
const std::map<int, std::queue<SensorData>> DataCollector::getSensorData() const noexcept
{
    return this->m_sensorData;
}
