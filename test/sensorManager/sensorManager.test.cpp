#include <catch2/catch_test_macros.hpp>
#include "sensorManager.hpp"

TEST_CASE("Testing sensor manager class", "[SensorManager],[Class]")
{
    SensorManager sensor;

    sensor.generate(3);
    REQUIRE_THROWS(sensor.getSensor(4));
    REQUIRE_NOTHROW(sensor.getSensor(1));
}