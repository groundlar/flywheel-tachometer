# Output interface in CapnProto schema definition language

# KE = I * w * w /2, in Joules (kg * m^2 / s^2)
# where
# I = moment of inertia (kg * m^2)
# w = angular velocity, radians per second (1/s)
struct AnalyzedRep {
    # TODO units!
    peak_velocity @0 :UInt32;
    max_accel @1 :UInt32;
    max_decel @2 :UInt32;
    velocity_curve @3 :VelocityCurve;
}

struct VelocityCurve {
    # Hertz frequency for the following velocity
    sample_rate_hz @0 :UInt16;
    # TODO units!
    velocities @1 :List(UInt32);
}

struct RawOutput {
    interrupt_timestamps @0 :List(UInt64)
}
