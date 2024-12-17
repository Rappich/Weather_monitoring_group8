#include <catch2/catch_test_macros.hpp>
#include "lifetimeStatistics.hpp"
#include "sensorManager.hpp"

TEST_CASE("Testing lifetime statistics class", "[Statistics],[RAM],[Storage],[Class]")
{
    {
        LifetimeStatistics stats{};
        SensorManager sensorManager;
        DataCollector *dataCollector = sensorManager.getDataCollector();

        dataCollector->addData(1, SensorData{1, 1, 1});
        REQUIRE(dataCollector->getSensorData(1) != nullptr);
        REQUIRE_NOTHROW(stats.calculateAll(dataCollector->getSensorData(1)));
    }

    {
        // LifetimeStatistics stats{};

        // const std::queue<SensorData> data{{{1, 1, 1}, {1, 1, 1}}};
        // stats.calculateAll(&data);

        // stats.getHumidity().avg;
        // CHECK(stats.getHumidity().avg == 1.0);
        // CHECK(stats.getHumidity().min == 1.0);
        // CHECK(stats.getHumidity().max == 1.0);

        // CHECK(stats.getTemperature().avg == 1);
        // CHECK(stats.getTemperature().min == 1);
        // CHECK(stats.getTemperature().max == 1);

        // CHECK(stats.getWindspeed().avg == 1);
        // CHECK(stats.getWindspeed().min == 1);
        // CHECK(stats.getWindspeed().max == 1);

        // stats.calculateAll(std::queue<SensorData>{{{2, 2, 2}, {2, 2, 2}}});
        // CHECK(stats.getHumidity().avg == 1.5);
        // CHECK(stats.getHumidity().min == 1);
        // CHECK(stats.getHumidity().max == 2);

        // CHECK(stats.getTemperature().avg == 1.5);
        // CHECK(stats.getTemperature().min == 1);
        // CHECK(stats.getTemperature().max == 2);

        // CHECK(stats.getWindspeed().avg == 1.5);
        // CHECK(stats.getWindspeed().min == 1);
        // CHECK(stats.getWindspeed().max == 2);
    }


}