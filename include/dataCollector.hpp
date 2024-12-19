#ifndef __DATA_COLLECTOR__
#define __DATA_COLLECTOR__

#include <mutex>
#include <atomic>
#include <map>
#include <vector>
#include <queue>
#include <memory>
#include <condition_variable>

#include "sensorData.hpp"

class DataCollector
{
public:
    DataCollector();

    void setDataReady(bool ready);

    void addData(unsigned int sensorId, SensorData data);
    const std::queue<SensorData> *getSensorData(unsigned int sensorId) noexcept;
    const std::map<unsigned int, std::queue<SensorData>> &getSensorData() noexcept;
    
private:
    std::map<unsigned int, std::queue<SensorData>> m_sensorData {};

    std::condition_variable m_dataReadySignal;
    std::atomic_bool m_dataReady;
    std::mutex m_mtx;
};

#endif