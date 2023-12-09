## Use Abaqus to read the 3D model prototype "Assemblage1.step"
# MPU6050 Complementary Filter with Servo Motor Control

This Arduino code utilizes the MPU6050 accelerometer and gyroscope sensor to calculate roll and pitch angles. The complementary filter is employed to fuse data from the accelerometer and gyroscope for improved accuracy. The corrected angles are then used to adjust the speed of two servo motors connected to pins 9 and 10.

## Hardware Requirements
- Arduino board
- MPU6050 sensor
- Two servo motors

## Software Dependencies
- [Wire library](https://www.arduino.cc/en/reference/wire)
- [MPU6050 library](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050)
- [Servo library](https://www.arduino.cc/en/Reference/Servo)

## Wiring Instructions
1. Connect the SDA and SCL pins of the MPU6050 to the corresponding pins on the Arduino board.
2. Connect the servo motors to pins 9 and 10 on the Arduino board.

## Code Explanation
1. The MPU6050 sensor is initialized, and servo motors are attached to pins 9 and 10 in the `setup()` function.

2. In the `loop()` function:
   - Accelerometer and gyroscope data are read from the MPU6050.
   - Roll and pitch angles are calculated from accelerometer data.
   - A complementary filter is applied to combine accelerometer and gyroscope data for more accurate angle measurements.
   - Motor speeds are adjusted based on the roll and pitch angles.
   - Servo angles are mapped from motor speeds and applied to the servo motors.

3. The `calculateMotorSpeed()` function adjusts the motor speed based on the roll or pitch angle.

4. Serial output displays the roll and pitch angles for debugging purposes.

## Configuration Parameters
- `alpha`: Complementary filter constant. Adjust as needed for your specific application.
- `baseSpeed`: Base motor speed. Adjust to set the baseline speed of the motors.
- `speedAdjustment`: Scaling factor for adjusting motor speed based on roll/pitch angle. Adjust the sign and scaling factor as needed.

## Notes
- Ensure that the MPU6050 and servo libraries are installed in your Arduino IDE.
- Adjust the servo motor pins, constants, and scaling factors according to your specific hardware and requirements.

Feel free to modify the code and parameters to suit your project's needs.
