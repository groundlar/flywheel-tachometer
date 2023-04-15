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
                           const Config &config) {
  // TODO saturation!
  // int32_t changes = count_changes_with_lambda(readings);
  int32_t changes = count_changes(readings);
  // Sample rate is in hertz: 1 hertz means 10^3 millis between readings.
  // millihertz := 1/1000 cycles per second = hertz * MILLIS
  return util::MILLIS * changes * config.sample_rate_hz / readings.size();
}

uint32_t raw_to_millirps(const std::vector<uint8_t> &readings,
                         const Config &config) {
  // One RPS is one Hertz, so just account for the sensors per revolution.
  return raw_to_millihertz(readings, config) / config.sensor_count;
}

uint32_t raw_to_milliradians_per_sec(const std::vector<uint8_t> &readings,
                                     const Config &config) {
  uint32_t millirps = raw_to_millirps(readings, config);
  // one rotation is 2*PI radians
  return static_cast<uint32_t>(millirps * 2 * PI);
}

// Encodes series of samples as milliradians per second at the output frequency
// specified in the passed configuration.
std::vector<uint32_t>
velocity_encode_milliradians_per_sec(const std::vector<uint64_t> &interrupt_us,
                                     const Config &config) {
  std::vector<uint32_t> velocities{};
  uint64_t output_interval_us = util::MICROS / config.output_hz;
  // TODO translate raw readings to config-specified hertz measurement.
  // Calculate average velocity for each interval using all measurements
  // within the window. If no measurements are present, extrapolate using
  // current velocity.
  return velocities;
}

uint32_t find_next_wave_valley(const std::vector<uint32_t> &vals,
                               uint32_t start_ind = 0) {
  // TODO low-pass filtering
  if (vals.size() < start_ind + 2) {
    return 0;
  }
  uint32_t min_index = start_ind;
  uint32_t min_value = vals[start_ind];
  for (uint32_t i = start_ind + 1; i < vals.size(); i++) {
    if (vals[i] < min_value) {
      min_index = i;
      min_value = vals[i];
    } else {
      break;
    }
  }
  return min_index;
}

// Destructively filters an array to a repetition ("cycle"),
// using ~0 RPM to ~0RPM as the bounds
void filter_rep(std::vector<uint32_t> &velocities, const Config &kConfig) {
  // TODO look for longer quiescent periods rather than local minimum?
  // Edge is local minimum value.
  uint32_t minimum_ind = find_next_wave_valley(velocities);
  velocities.erase(velocities.begin(), velocities.begin() + minimum_ind);

  // Empirical value, typically a full repetition will take >0.5s;
  uint32_t min_samples_for_rep = kConfig.output_hz / 2;
  // Edge is local minimum value.
  uint32_t maximum_ind = find_next_wave_valley(velocities, min_samples_for_rep);
  velocities.erase(velocities.begin() + maximum_ind, velocities.end());
}

std::vector<uint32_t> encode_next_rep_as_milliradians_per_sec(
    const std::vector<uint64_t> &interrupt_us, const Config &config) {
  std::vector<uint32_t> velocities =
      velocity_encode_milliradians_per_sec(interrupt_us, config);
  util::emwa_vector(velocities);
  filter_rep(velocities, config);
  return velocities;
}

uint32_t find_max_accel(std::vector<uint32_t> &velocities,
                        const Config &config) {
  // Looks at the changes in velocities (maybe groups of 3 velocities?)
  // to find the maximum (positive) acceleration.
  // TODO
  return 0;
}
uint32_t find_max_decel(std::vector<uint32_t> &velocities,
                        const Config &config) {
  // Looks at the changes in velocities (maybe groups of 3 velocities?)
  // to find the maximum deceleration (negative acceleration).
  // TODO
  return 0;
}

uint32_t find_max_speed(std::vector<uint32_t> &rep) {
  return *std::max_element(rep.begin(), rep.end());
}

// The output of this class.
// Contains inertia-agnostic measurements as that will be configured
// on the client and applied as a scaling factor.
struct Output {
  // TODO units!
  std::vector<uint32_t> velocity_curve;
  uint32_t max_accel;
  uint32_t max_decel;
  uint32_t max_speed;
};

Output raw_to_output(std::vector<uint64_t> interrupt_us, const Config &config) {
  Output out{};
  // TODO static initialization of velocity vector and max size.
  // 1. Find rep boundary, encode as velocities
  out.velocity_curve =
      encode_next_rep_as_milliradians_per_sec(interrupt_us, config);
  // Now we have a smoothed velocity curve at the specified sampling rate.
  // Find the maximum accelertaion, deceleration, and velocity within the rep.
  out.max_accel = find_max_accel(out.velocity_curve, config);
  out.max_decel = find_max_decel(out.velocity_curve, config);
  out.max_speed = find_max_speed(out.velocity_curve);
  return out;
}

} // namespace lib_rpm_calculation