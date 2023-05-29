# flywheel-tachometer
Units:
  * Inertia units: `kg * m^2`
  * Force units: Newton: `kg * m / s^2`
  * Joule: Newton meter : `kg * m^2 / s^2`
  * Power units: Joule / sec: Newton meter / sec: `kg * m^2 / s^3`

So if we have inertia stored in-app, we need to report `1/s^3` to make the units work out.

## Flywheel kinetics
Approximately 15 revolutions for a high-ROM kbox-analogue (zercher jefferson curl).
The lower bound for concentric phase is ~0.5 seconds.
This leaves us at an average of 30 RPM for the movement.
With 4 sensors per revolution, that's 120 interrupts per second, or approximately every 10ms.
(This is intended as an upper bound, realistically a half-second concentric probably achieves ~10 revolutions with an appreciable load.)



## TODO
- capnproto exception implementation
- runtime / scheduler
- BLE connection
- BLE data transfer
