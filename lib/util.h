#ifndef LIB_UTIL_H_
#define LIB_UTIL_H_

#include <cstdint>

namespace util {

inline constexpr int32_t MICROS = 1000000;
inline constexpr int32_t MILLIS = 1000;
inline constexpr int32_t HERTZ_TO_RPM = 60;

uint32_t exp_average(uint32_t average, uint32_t next,
                     uint16_t inverse_smoothing) {
  // For weight 0 < w < 1,
  // EMWA := x_0 * w + (1 - w) * x_1
  // Let z = 1/w, then
  // EMWA = x_0 / z + (1 - 1/z) * x_1 = (x_0 + x_1) / z + x1
  return static_cast<uint32_t>((average - next) / inverse_smoothing + next);
}

} // namespace util

#endif // LIB_UTIL_H_