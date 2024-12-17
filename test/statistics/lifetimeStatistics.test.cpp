#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_message.hpp>
#include "lifetimeStatistics.hpp"
#include "sensorManager.hpp"

TEST_CASE("Testing lifetime statistics class", "[Statistics],[RAM],[Storage],[Class]")
{
    // {
    //     LifetimeStatistics stats{};
    //     // SensorManager sensorManager;
    //     DataCollector dataCollector = DataCollector();

    //     dataCollector.addData(1, SensorData{1, 1, 1});
    //     CHECK(dataCollector.getSensorData(1) != nullptr);
        
        
    //     // try {
    //     //     REQUIRE_NOTHROW(stats.calculateAll(nullptr));
    //     // } catch (std::exception &e)
    //     // {
    //     //     std::cout << e.what() << std::endl;
    //     // }
    // }

    // {
    //     LifetimeStatistics stats{};

    //     const std::queue<SensorData> data{{{1, 1, 1}, {1, 1, 1}}};
    //     stats.calculateAll(&data);

    //     stats.getHumidity().avg;
    //     CHECK(stats.getHumidity().avg == 1.0);
    //     REQUIRE(stats.getHumidity().min == 1.0);
    //     REQUIRE(stats.getHumidity().max == 1.0);

    //     CHECK(stats.getTemperature().avg == 1);
    //     CHECK(stats.getTemperature().min == 1);
    //     CHECK(stats.getTemperature().max == 1);

    //     CHECK(stats.getWindspeed().avg == 1);
    //     CHECK(stats.getWindspeed().min == 1);
    //     CHECK(stats.getWindspeed().max == 1);

    //     auto queue = std::queue<SensorData>{{{2, 2, 2}, {2, 2, 2}}};
    //     stats.calculateAll(&queue);
    //     CHECK(stats.getHumidity().avg == 1.5);
    //     CHECK(stats.getHumidity().min == 1);
    //     CHECK(stats.getHumidity().max == 2);

    //     CHECK(stats.getTemperature().avg == 1.5);
    //     CHECK(stats.getTemperature().min == 1);
    //     CHECK(stats.getTemperature().max == 2);

    //     CHECK(stats.getWindspeed().avg == 1.5);
    //     CHECK(stats.getWindspeed().min == 1);
    //     CHECK(stats.getWindspeed().max == 2);
    // }


}