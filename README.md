## Arduino heart rate/pulse sensors
**A comparison of pulse sensors for Arduino.**
- **Pulse sensor from https://pulsesensor.com/** *Unfortunately the older version, I bought it a long time ago and I don't know if mine is the original or cheap clone, probably there are differences not only in price.*
- **DFRobot heart rate sensor (SON1303)**
- **MH-ET Live Pulse sensor (MAX30102)**
- **Iduino pulse sensor** *Please don't you dare to bring this crap to my classes trying to do semester project!*

*Remember, these modules aren't certified for medical use. They don't provide enough accuracy to correctly measure P, Q, R, S, T, U intervals, you can see them but they're too noisy. These sensors are mostly used in wearable devices.*

### Example code:
- **heart_rate_analog_read_auto_threshold:** quick and dirty way to see the pulse curve in serial plotter and basic usage of time-series data to compute pulse threshold.
- **heart_rate_analog_measure:** custom implementation of heart beat rate from analog input. *Without interrupts.*