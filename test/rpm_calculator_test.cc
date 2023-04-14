#include "lib/rpm_calculation.h"
#include "lib/util.h"
#include <gtest/gtest.h>

TEST(RpmTest, raw_to_millihertz_empty) {
  std::vector<uint8_t> empty_readings = {};
  std::vector<int16_t> sample_rates = {0, 10, 100};
  std::vector<int16_t> sensor_counts = {0, 1, 4};
  for (int16_t rate : sample_rates) {
    for (int16_t sensors : sensor_counts) {
      int32_t result =
          lib_rpm_calculation::raw_to_millihertz(empty_readings, rate);
      EXPECT_EQ(result, 0);
      result =
          lib_rpm_calculation::raw_to_millirpm(empty_readings, rate, sensors);
      EXPECT_EQ(result, 0);
    }
  }
}

TEST(RpmTest, raw_to_millihertz_alternating_single) {
  std::vector<uint8_t> readings = {1, 0, 1, 0, 1};
  uint16_t sample_rate = 1;
  uint32_t expected = util::MILLIS * 4 / 5; // 4 changes at 1 hz;
  uint32_t result =
      lib_rpm_calculation::raw_to_millihertz(readings, sample_rate);
  EXPECT_EQ(result, expected);
}

TEST(RpmTest, raw_to_millihertz_alternating_sample) {
  std::vector<uint8_t> readings = {0, 1, 0, 1, 0, 1};
  std::vector<uint16_t> sample_rates = {1, 4, 400, 1000, 10000};
  // Assumes readings alternates between 0 and 1!
  uint16_t oscillations = readings.size() - 1;
  for (auto sample_rate : sample_rates) {
    uint32_t expected =
        util::MILLIS * sample_rate * oscillations / readings.size();
    uint32_t result =
        lib_rpm_calculation::raw_to_millihertz(readings, sample_rate);
    EXPECT_EQ(result, expected);
  }
}
