#include <Wire.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

#define VIBRATOR 9  // Analog output pin that the vibrator is attached to
#define LED 6       // Analog output pin that the LED is attached to

// Vibration patterns
enum PatternState { NONE,
                    POKE,
                    ANGRY,
                    HAPPY,
                    FEAR,
                    SAD,
                    ANXIETY };

// Vibration state
PatternState patternState = NONE;

// Vibration values
#define POW_LOW 100
#define POW_MED 150
#define POW_HIGH 255

int lightValue = 5;
int minLight = 0;
int maxLight = 10;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize LED
  pinMode(LED, OUTPUT);

  // Init IMU sensor
  if (!mpu.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1) {
      delay(10);
    }
  }

  // Configure IMU sensor
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sendGyroData();
  handleGesture();
  playPattern();

  // Light
  int mappedLight = map(lightValue, 0, 10, 0, 255);
  analogWrite(LED, mappedLight);
}

void sendGyroData() {
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

void handleGesture() {
  while(Serial.available()) {
    int value = Serial.read();

    switch (value) {
      case 0:
        patternState = NONE;
        break;
      case 1:
        patternState = ANGRY;
        lessLight();
        break;
      case 2:
        patternState = HAPPY;
        moreLight();
        break;
      case 3:
        patternState = POKE;
        break;
      case 4:
        patternState = FEAR;
        break;
      default:
        patternState = NONE;
        break;
    }

  }
}

void lessLight() {
  if(lightValue == minLight) return;
  lightValue--;
}

void moreLight() {
  if(lightValue == maxLight) return;
  lightValue++;
}

void playPattern() {
  switch (patternState) {
    case NONE:
      patternNone();
      break;
    case POKE:
      patternPoke();
      break;
    case ANGRY:
      patternAngry();
      break;
    case HAPPY:
      patternHappy();
      break;
    case FEAR:
      patternFear();  //rapide, exicté
      break;
    case SAD:  //endormi
      patternSad();
      break;
    case ANXIETY:
      patternAnxiety();
      break;
  }
}
