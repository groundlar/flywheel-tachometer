#include "lib/rpm_calculation.h"
#include "lib/util.h"
#include <numeric>
#include <vector>

namespace lib_rpm_calculation {

int32_t count_changes(const std::vector<uint8_t> &vals) {
  if (vals.size() < 2) {
    return 0;
  }
  int32_t changes = 0;
  int32_t last = vals[0];
  for (uint32_t i = 1; i < vals.size(); i++) {
    if (vals[i] != last) {
      changes++;
    }
    last = vals[i];
  }
  return changes;
}

uint32_t raw_to_millihertz(const std::vector<uint8_t> &readings,
                           uint16_t sample_rate_hz) {
  // TODO saturation!
  // int32_t changes = count_changes_with_lambda(readings);
  int32_t changes = count_changes(readings);
  // Sample rate is in hertz: 1 hertz means 10^3 millis between readings.
  // millihertz := 1/1000 cycles per second = hertz * MILLIS
  return util::MILLIS * changes * sample_rate_hz / readings.size();
}

uint32_t raw_to_millirpm(const std::vector<uint8_t> &readings,
                         uint16_t sample_rate_hz, uint16_t sensor_count) {
  return raw_to_millihertz(readings, sample_rate_hz) * util::HERTZ_TO_RPM /
         sensor_count;
}

} // namespace lib_rpm_calculation