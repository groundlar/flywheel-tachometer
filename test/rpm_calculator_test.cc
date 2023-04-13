#include <gtest/gtest.h>
#include "lib/rpm_calculation.h"

TEST(RpmTest, raw_to_microhertz_empty) {
    std::vector<uint8_t> empty_readings = {};
    std::vector<int16_t> sample_rates = {0, 10, 100};
    std::vector<int16_t> sensor_counts = {0, 1, 4};
    for (int16_t rate : sample_rates) {
        for (int16_t sensors: sensor_counts) {
          int32_t result = lib_rpm_calculation::raw_to_microhertz(
              empty_readings, rate, sensors);
          EXPECT_EQ(result, 0);
        }
    }
}

TEST(RpmTest, raw_to_microhertz_alternating_default_sensors) {
    std::vector<uint8_t> readings = {1,0,1,0,1,0};
    uint16_t sample_rate = 1;
    int32_t result = lib_rpm_calculation::raw_to_microhertz(readings, sample_rate);
    EXPECT_EQ(result, 1 * lib_rpm_calculation::MICROS);
}

TEST(RpmTest, raw_to_microhertz_alternating_4_sensors) {
    std::vector<uint8_t> readings = {1,0,1,0,1,0};
    uint16_t sample_rate = 1;
    int32_t result = lib_rpm_calculation::raw_to_microhertz(readings, sample_rate);
    EXPECT_EQ(result, 1 * lib_rpm_calculation::MICROS / 4);
}
