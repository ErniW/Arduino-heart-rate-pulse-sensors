## Arduino heart rate/pulse sensors
**A comparison of pulse sensors for Arduino.**
- **Pulse sensor from https://pulsesensor.com/** *Unfortunately the older version, I bought it a long time ago and I don't know if mine is the original or cheap clone, probably there are differences not only in price. Main drawback is its sensitivity to finger movement.*
- **DFRobot heart rate sensor (SON1303)** *Can provide digital and analog signal.*
- **MH-ET Live Pulse sensor (MAX30102)** *Communicates via I2C, can provide heart rate and pulse oximetry. Someone didn't thought about not putting all passive electronics and pin holes close to sensor so you won't touch all that things if you have large finger. Measurments through Sparkfun library looks inconsistent.*
- **Iduino pulse sensor** *Waste of money. Please don't you dare to bring this crap to my classes trying to do semester project!*

### What you can measure?
*Remember, these modules are fine but they aren't certified for medical use. They don't provide enough accuracy to correctly measure P, Q, R, S, T intervals even if you can see them. These sensors are mostly used in wearable smart devices. Possibilities of such sensors in healthcare should be investigated. A friend of mine told me that with better resolution you can measure the pulse characteristic through calculating its slope on each step instead of thresholds.*
- **BPM: Beats Per Minute.** Measured as R-R interval.
- **HRV: Heart Rate Variability.** Standard deviation of changes in R-R intervals sequence. High HRV means we are more relaxed, opposite means we are stressed (need to confirm).
- **PPT: Pulse Transit Time. (?)** Requires two sensors. Measures the time it takes the pulse to transfer the blood. Measures delays between QRS segment of synchronized sensors (need to confirm how it works and whether it's doable with non-medical sensors).

### Example code:
- **heart_rate_analog_read_auto_threshold:** quick and dirty way to see the pulse curve in serial plotter and basic usage of time-series data to calibrate pulse threshold.
- **heart_rate_analog_measure:** simple custom implementation of heart beat rate from analog input. *Without interrupts. Uses queue data structure and state machine design pattern. Requires proper timing depending on your needs (and frequency of microcontroller).*
- **DFRobot_heart_rate_sensor:** using DFRobot library. *For analog mode heart_rate_analog_measure is fine.*
- For **MAX30102** I've been working with Sparkfun library, however the variation between measurements looks high.

*TODO: During our classes we had difficulties connecting 4 sensors at once, the results were overlaping, however it was probably because of incorrectly using memory allocation for Arduino UNO.*