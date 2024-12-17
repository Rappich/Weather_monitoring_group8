#include <catch2/catch_test_macros.hpp>
#include "dataStatistics.hpp"

TEST_CASE("Testing data statistics class", "[Statistics],[Storage],[Class]")
{
    DataStatistics stats{};
    // SensorManager sensorManager;
    DataCollector dataCollector = DataCollector();

    dataCollector.addData(1, SensorData{1, 1, 1});
    CHECK(dataCollector.getSensorData(1) != nullptr);

    const std::queue<SensorData> data{{{1, 1, 1}, {1, 1, 1}}};
    stats.calculateAll(&data);

    stats.getHumidity().avg;
    CHECK(stats.getHumidity().avg == 1.0);
    REQUIRE(stats.getHumidity().min == 1.0);
    REQUIRE(stats.getHumidity().max == 1.0);

    CHECK(stats.getTemperature().avg == 1);
    CHECK(stats.getTemperature().min == 1);
    CHECK(stats.getTemperature().max == 1);

    CHECK(stats.getWindspeed().avg == 1);
    CHECK(stats.getWindspeed().min == 1);
    CHECK(stats.getWindspeed().max == 1);

    auto queue = std::queue<SensorData>{{{2, 2, 2}, {2, 2, 2}}};
    stats.calculateAll(&queue);
    CHECK(stats.getHumidity().avg == 2);
    CHECK(stats.getHumidity().min == 2);
    CHECK(stats.getHumidity().max == 2);

    CHECK(stats.getTemperature().avg == 2);
    CHECK(stats.getTemperature().min == 2);
    CHECK(stats.getTemperature().max == 2);

    CHECK(stats.getWindspeed().avg == 2);
    CHECK(stats.getWindspeed().min == 2);
    CHECK(stats.getWindspeed().max == 2);

    auto queue2 = std::queue<SensorData>{{{3, 2, 2}, {3, 2, 2}, {6, 8, 5}}};
    stats.calculateAll(&queue2);
    
    CHECK(stats.getHumidity().avg == 3);
    CHECK(stats.getHumidity().min == 2);
    CHECK(stats.getHumidity().max == 5);

    CHECK(stats.getTemperature().avg == 4);
    CHECK(stats.getTemperature().min == 2);
    CHECK(stats.getTemperature().max == 8);

    CHECK(stats.getWindspeed().avg == 4);
    CHECK(stats.getWindspeed().min == 3);
    CHECK(stats.getWindspeed().max == 6);
}