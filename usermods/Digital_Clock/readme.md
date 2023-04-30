# Digital Clock usermod

This usermod allows WLED to run on the 3D printed 7 segment digital clock.
Code is largely based on https://github.com/hwtronics/clock-7seg-fw-WLED by m.gazzarri
https://www.hwtronics.com/2021/04/08/7-segment-digital-clock-firmware-wled-powered/

Supported:
- RTC (with RTC usermod)
- Standard WLED time features (NTP, DST, timezones)

## Installation 

Compile and upload to clock using the `d1_mini_digital_clock` PlatformIO environment
Once uploaded (the clock can be flashed like any wemos module)