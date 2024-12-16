#ifndef __DATA_COLLECTOR__
#define __DATA_COLLECTOR__

#include <mutex>
#include <atomic>
#include <map>
#include <vector>
#include <queue>

#include "sensorData.hpp"

class DataCollector
{
public:
    DataCollector();

    void resetFlag();
    void setDataReady(bool ready);

    void addData(int sensorId, SensorData data);
    const std::queue<SensorData> *getSensorData(int sensorId) const noexcept;
    const std::map<int, std::queue<SensorData>> getSensorData() const noexcept;
    
private:
    std::map<int, std::queue<SensorData>> m_sensorData {};
    std::mutex mtx;

    bool dataReady;
};

#endif