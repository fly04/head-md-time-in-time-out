#include <Wire.h>
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
  sendAccGyroData();
  handleGesture();

  delay(10);
}

void handleGesture() {

  if (Serial.available() > 0) {
    // Read a string of characters from the serial port until the '!' character
    int value = Serial.read();

    if (value == 0) {
      patternNone();
    } else if (value == 1) {
      // Print the string to the serial monitor
      patternAngry();
    } else {
      patternTest();
    }
  }

  // if (Serial.available() > 0) {
  //   char gesture = Serial.read();
  //   Serial.println(gesture);
  //   switch (gesture) {
  //     case 0:
  //       patternNone();
  //       break;
  //     case 1:
  //       patternAngry();
  //       break;
  //     default:
  //       break;
  //   }
  // }
}


void sendAccGyroData() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 12, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  // print the sensor data in CSV format
  Serial.print(AcX);
  Serial.print(',');
  Serial.print(AcY);
  Serial.print(',');
  Serial.print(AcZ);
  Serial.print(',');
  Serial.print(GyX);
  Serial.print(',');
  Serial.print(GyY);
  Serial.print(',');
  Serial.print(GyZ);

  Serial.println();
}
