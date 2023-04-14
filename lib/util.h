#ifndef LIB_UTIL_H_
#define LIB_UTIL_H_

#include <cstdint>

#define PI 3.14159

namespace util {

inline constexpr int32_t MICROS = 1000000;
inline constexpr int32_t MILLIS = 1000;
inline constexpr int32_t HERTZ_TO_RPM = 60;
inline constexpr uint32_t KILO_PI = static_cast<uint32_t>(MILLIS * PI);

uint32_t exp_average(uint32_t average, uint32_t next, uint16_t inverse_coeff) {
  // For weight 0 < w < 1,
  // EMWA := x_0 * w + (1 - w) * x_1
  // Let z = 1/w, then
  // EMWA = x_0 / z + (1 - 1/z) * x_1 = (x_0 - x_1) / z + x_1
  int32_t weighted_sum = average + next * (inverse_coeff - 1);
  return static_cast<uint32_t>(weighted_sum / inverse_coeff);
}

} // namespace util

#endif // LIB_UTIL_H_