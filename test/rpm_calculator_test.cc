#include "lib/rpm_calculation.h"
#include "lib/util.h"
#include <gtest/gtest.h>

TEST(RpmTest, raw_to_millihertz_empty) {
  lib_rpm_calculation::Config config{};
  std::vector<uint8_t> empty_readings = {};
  std::vector<int16_t> sample_rates = {0, 10, 100};
  std::vector<int16_t> sensor_counts = {0, 1, 4};
  for (int16_t rate : sample_rates) {
    for (int16_t sensors : sensor_counts) {
      config.sensor_count = sensors;
      config.sample_rate_hz = rate;
      int32_t result =
          lib_rpm_calculation::raw_to_millihertz(empty_readings, config);
      EXPECT_EQ(result, 0);
      result = lib_rpm_calculation::raw_to_millirps(empty_readings, config);
      EXPECT_EQ(result, 0);
    }
  }
}

TEST(RpmTest, raw_to_millihertz_alternating_single) {
  lib_rpm_calculation::Config config{};
  std::vector<uint8_t> readings = {1, 0, 1, 0, 1};
  uint32_t expected = util::MILLIS * 4 / 5; // 4 changes at 1 hz;
  uint32_t result = lib_rpm_calculation::raw_to_millihertz(readings, config);
  EXPECT_EQ(result, expected);
}

TEST(RpmTest, raw_to_millihertz_alternating_sample) {
  lib_rpm_calculation::Config config{};
  std::vector<uint8_t> readings = {0, 1, 0, 1, 0, 1};
  std::vector<uint16_t> sample_rates = {1, 4, 400, 1000, 10000};
  // Assumes readings alternates between 0 and 1!
  uint16_t oscillations = readings.size() - 1;
  for (auto sample_rate : sample_rates) {
    config.sample_rate_hz = sample_rate;
    uint32_t expected =
        util::MILLIS * sample_rate * oscillations / readings.size();
    uint32_t result = lib_rpm_calculation::raw_to_millihertz(readings, config);
    EXPECT_EQ(result, expected);
  }
}