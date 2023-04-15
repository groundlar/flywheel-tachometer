#ifndef LIB_RPM_CALCULATION_H_
#define LIB_RPM_CALCULATION_H_

#include <cstdint>
#include <vector>

namespace lib_rpm_calculation {

struct Config {
  uint16_t sensor_count = 1;
  uint16_t sample_rate_hz = 1;
  uint8_t output_hz = 20;
  uint8_t inverse_emwa_coefficient = 4;
};

// TODO we might rather trigger on high edges, rather than sampling at a fixed
// frequency.
// TODO encapsulate into class which takes config.
uint32_t raw_to_millihertz(const std::vector<uint8_t> &readings,
                           const Config &config);
uint32_t raw_to_millirps(const std::vector<uint8_t> &readings,
                         const Config &config);
uint32_t raw_to_radians_per_sec(const std::vector<uint8_t> &readings,
                                const Config &config);

} // namespace lib_rpm_calculation

#endif // LIB_RPM_CALCULATION_H_