#include <catch2/catch_test_macros.hpp>
#include "dataCollector.hpp"
#include "measurementData.hpp"

TEST_CASE("Testing DataCollector class", "[DataCollector],[Class],[Data]")
{
    DataCollector dataCollector;

    dataCollector.addData(1, {});
    dataCollector.setDataReady(true);
    CHECK(dataCollector.getSensorData(1)->size() == 1);

    // dataCollector.addData(1, {});
    // dataCollector.setDataReady(true);
    // CHECK(dataCollector.getSensorData().at(1).size() == 2);

    // dataCollector.addData(2, {});
    // dataCollector.setDataReady(true);
    // CHECK_FALSE(dataCollector.getSensorData().at(1).empty());
    // CHECK(dataCollector.getSensorData(2) != nullptr);

    // dataCollector.setDataReady(true);
    // CHECK(dataCollector.queryData(1) == nullptr);

    // dataCollector.setDataReady(true);
    // CHECK(dataCollector.queryData(1) != nullptr);
}

TEST_CASE("Testing DataCollector methods", "[DataCollector],[Class],[Data],[SensorData]")
{
    DataCollector dataCollector;

    dataCollector.addData(0, SensorData{10, 20, 30});
    dataCollector.addData(1, SensorData{10, 20, 30});
    dataCollector.addData(2, SensorData{10, 20, 30});

    CHECK(dataCollector.getSensorData(0)->front().windspeed == 10);
    CHECK(dataCollector.getSensorData(1)->front().temperature == 20);
    CHECK(dataCollector.getSensorData(2)->front().humidity == 30);
}