#ifndef LIB_UTIL_H_
#define LIB_UTIL_H_

#include <cstdint>
#include <vector>

#define PI 3.14159

namespace util {

inline constexpr int32_t MICROS = 1000000;
inline constexpr int32_t MILLIS = 1000;
inline constexpr int32_t HERTZ_TO_RPM = 60;
inline constexpr uint32_t KILO_PI = static_cast<uint32_t>(MILLIS * PI);

// Calculates the exponentially-weighted average for the provided average, next
// reading, and inverse weighting coefficient. Typically coefficients are
// between 0.2 and 0.3 => inverse between 3 and 5. See
// https://itl.nist.gov/div898/handbook/pmc/section7/pmc7.htm
inline uint32_t exp_average(uint32_t average, uint32_t next,
                            uint16_t inverse_coeff = 4) {
  // For weight 0 < w < 1,
  // EMWA := x_0 * w + (1 - w) * x_1
  // Let z = 1/w, then
  // EMWA = x_0 / z + (1 - 1/z) * x_1 = (x_0 - x_1) / z + x_1
  int32_t weighted_sum = average + next * (inverse_coeff - 1);
  return static_cast<uint32_t>(weighted_sum / inverse_coeff);
}

inline void emwa_vector(std::vector<uint32_t> input,
                        uint16_t inverse_coeff = 4) {
  if (input.size() < 2) {
    return;
  }
  uint32_t avg = input[0];
  for (uint32_t i = 0; i < input.size(); i++) {
    input[i] = exp_average(avg, input[i], inverse_coeff);
  }
}

} // namespace util

#endif // LIB_UTIL_H_