#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

MPU6050 mpu;
Servo motorServo1;
Servo motorServo2;

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;

float alpha = 0.98; // Complementary filter constant why ?
float roll, pitch;

void setup() {
  Serial.begin(9600);

  Wire.begin();
  mpu.initialize();
  motorServo1.attach(9); // servo motor in pin 9
  motorServo2.attach(10); // servo motor in pin 10
  
}

void loop() {
  // Read accelerometer and gyroscope data
  mpu.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);

  // Calculate roll and pitch from accelerometer data
  float accRoll = atan2(accY, accZ) * (180.0 / PI);
  float accPitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * (180.0 / PI);

  // Complementary filter to combine accelerometer and gyroscope data
  roll = alpha * (roll + gyroX * 0.001) + (1 - alpha) * accRoll;
  pitch = alpha * (pitch + gyroY * 0.001) + (1 - alpha) * accPitch;

  // Adjust motor speed based on the roll angle
  int motorSpeed1 = calculateMotorSpeed(roll);

 // Adjust motor speed based on the pitch angle
  int motorSpeed2 = calculateMotorSpeed(pitch);

  // Map the motor speed to the servo angle (assuming the servo is configured for 0-180 degrees)
  int servoAngle1 = map(motorSpeed1, 1000, 2000, 0, 180);

  // Map the motor speed to the servo angle (assuming the servo is configured for 0-180 degrees)
  int servoAngle2 = map(motorSpeed2, 1000, 2000, 0, 180);

  // Set the servo angle for corrected roll
  motorServo1.write(servoAngle1);

 // Set the servo angle for corrected pitch
  motorServo2.write(servoAngle2);

  // Print the orientation angles and motor speed
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print(" Pitch: ");
  Serial.print(pitch);
  delay(10);
}

int calculateMotorSpeed(float input) {
  // Adjust motor speed based on the roll/pitch angle
  // The counterweight moves in the opposite direction of the roll/pitch
  // scaling factor and direction???
  int baseSpeed = 1500; // Adjust???
  int speedAdjustment = static_cast<int>(-1 * input); // Adjust the sign and scaling factor as needed
  return constrain(baseSpeed + speedAdjustment, 1000, 2000); // Constrain the output to the motor control range
}
