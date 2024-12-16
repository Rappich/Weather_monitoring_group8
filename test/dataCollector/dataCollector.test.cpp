#include <catch2/catch_test_macros.hpp>
#include "dataCollector.hpp"

TEST_CASE("Testing DataCollector class", "[DataCollector],[Class],[Data]") {
    DataCollector dataCollector;

    dataCollector.addData(1, {});
    CHECK(dataCollector.getSensorData(1)->size() == 1);
    
    dataCollector.addData(1, {});
    CHECK(dataCollector.getSensorData().at(1).size() == 2);

    CHECK_FALSE(dataCollector.getSensorData().at(1).empty());
    CHECK(dataCollector.getSensorData(2) == nullptr);

    CHECK(dataCollector.queryData(1) == nullptr);

    dataCollector.setDataReady(true);
    CHECK(dataCollector.queryData(1) != nullptr);
}