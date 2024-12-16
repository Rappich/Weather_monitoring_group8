#ifndef __DATA_COLLECTOR__
#define __DATA_COLLECTOR__

#include <mutex>
#include <atomic>
#include <map>
#include <vector>
#include <queue>
#include <memory>

#include "sensorData.hpp"

class DataCollector
{
public:
    DataCollector();

    void resetFlag();
    void setDataReady(bool ready);

    void addData(unsigned int sensorId, SensorData data);
    const std::queue<SensorData> *getSensorData(unsigned int sensorId) const noexcept;
    const std::map<unsigned int, std::queue<SensorData>> getSensorData() const noexcept;
    
    std::shared_ptr<SensorData> queryData(unsigned int sensorId);
private:
    std::map<unsigned int, std::queue<SensorData>> m_sensorData {};
    std::mutex mtx;

    bool dataReady;
};

#endif