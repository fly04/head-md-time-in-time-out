#include <Wire.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);

  // init IMU sensor
  if (!mpu.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1) {
      delay(10);
    }
  }

  // configure IMU sensor
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;

  // read the acceleration and gyroscope data
  mpu.getEvent(&a, &g, &temp);

  // print the sensor data in CSV format
  Serial.print(a.acceleration.x, 3);
  Serial.print(',');
  Serial.print(a.acceleration.y, 3);
  Serial.print(',');
  Serial.print(a.acceleration.z, 3);
  Serial.print(',');
  Serial.print(g.gyro.x, 3);
  Serial.print(',');
  Serial.print(g.gyro.y, 3);
  Serial.print(',');
  Serial.print(g.gyro.z, 3);

  Serial.println();

  delay(10);
}
