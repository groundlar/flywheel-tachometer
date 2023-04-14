#ifndef LIB_RPM_CALCULATION_H_
#define LIB_RPM_CALCULATION_H_

#include <cstdint>
#include <vector>

namespace lib_rpm_calculation {

uint32_t raw_to_millihertz(const std::vector<uint8_t> &readings,
                           uint16_t sample_rate_hz);
uint32_t raw_to_millirpm(const std::vector<uint8_t> &readings,
                         uint16_t sample_rate_hz, uint16_t sensor_count = 1);

} // namespace lib_rpm_calculation

#endif // LIB_RPM_CALCULATION_H_