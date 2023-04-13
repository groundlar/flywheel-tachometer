#ifndef LIB_RPM_CALCULATION_H_
#define LIB_RPM_CALCULATION_H_

#include <cstdint>
#include <vector>

namespace lib_rpm_calculation {

inline constexpr int32_t MICROS = 1000000;
inline constexpr int32_t MILLIS = 1000;

int32_t raw_to_microhertz(const std::vector<uint8_t>& readings, int16_t sample_rate_hz, uint16_t sensor_count=1);

} // namespace lib_rpm_calculation 

#endif // LIB_RPM_CALCULATION_H_