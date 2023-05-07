# flywheel-tachometer
Units:
  * Inertia units: `kg * m^2`
  * Force units: Newton: `kg * m / s^2`
  * Joule: Newton meter : `kg * m^2 / s^2`
  * Power units: Joule / sec: Newton meter / sec: `kg * m^2 / s^3`

So if we have inertia stored in-app, we need to report `1/s^3` to make the units work out.


## TODO
- capnproto exception implementation
- runtime / scheduler
- BLE connection
- BLE data transfer