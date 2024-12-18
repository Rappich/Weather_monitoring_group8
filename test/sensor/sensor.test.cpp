#include <catch2/catch_test_macros.hpp>
#include "sensor.hpp"

TEST_CASE("Testing sensor class", "[Sensor],[Class],[Generation]")
{
    Sensor sensor(1);

    CHECK(sensor.getID() == 1);

    sensor.readData();
    CHECK(sensor.getData().humidity >= 0);
    CHECK(sensor.getData().humidity <= 100.0);
    CHECK(sensor.getData().temperature >= -40.0);
    CHECK(sensor.getData().temperature <= 40.0);
    CHECK(sensor.getData().windspeed >= 0);
    CHECK(sensor.getData().windspeed <= 30.0);

    sensor.readData();
    CHECK(sensor.getData().humidity >= 0);
    CHECK(sensor.getData().humidity <= 100.0);
    CHECK(sensor.getData().temperature >= -40.0);
    CHECK(sensor.getData().temperature <= 40.0);
    CHECK(sensor.getData().windspeed >= 0);
    CHECK(sensor.getData().windspeed <= 30.0);

    sensor.readData();
    CHECK(sensor.getData().humidity >= 0);
    CHECK(sensor.getData().humidity <= 100.0);
    CHECK(sensor.getData().temperature >= -40.0);
    CHECK(sensor.getData().temperature <= 40.0);
    CHECK(sensor.getData().windspeed >= 0);
    CHECK(sensor.getData().windspeed <= 30.0);
}