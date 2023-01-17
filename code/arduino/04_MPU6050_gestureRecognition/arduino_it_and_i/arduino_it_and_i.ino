#include <Wire.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

#define VIBRATOR 9  // Analog output pin that the vibrator is attached to
#define LED 6       // Analog output pin that the LED is attached to

// Vibration patterns
enum PatternState { NONE,
                    ANGRY,
                    HAPPY,
                    ANXIETY
                    // ,
                    // POKE,
                    // FEAR,
                    // SAD,
                    // ANXIETY
};

// Vibration state
PatternState patternState = NONE;
// PatternState lastState = NONE;


// Vibration values
#define POW_LOW 100
#define POW_MED 150
#define POW_HIGH 255

int lightValue = 5;
int minLight = 0;
int maxLight = 10;

unsigned long enterStateTimer = 0;
boolean canChange = true;


int happyValue = 50;
bool happyRising = true;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize LED
  pinMode(LED, OUTPUT);

  // Init IMU sensor
  if (!mpu.begin()) {
    // Serial.println("Failed to initialize IMU!");
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

  // debug();

  int mappedLight = map(lightValue, 0, 10, 0, 255);
  analogWrite(LED, mappedLight);

  delay(100);
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
  while (Serial.available()) {
    int value = Serial.read();

    if (!canChange) return;

    if (value != 0) {
      enterStateTimer = millis();
      canChange = false;
    }

    if (value == 0) {
      // lastState = NONE;

    } else if (value == 1 || value == 'h') {
      // if(lastState == HAPPY) return;
      happyValue = 50;
      happyRising = true;
      patternState = HAPPY;
      moreLight();

    } else if (value == 2 || value == 'a') {
      // if(lastState == ANGRY) return;
      patternState = ANGRY;
      lessLight();
    } else if (value == 10 || value == 'x') {
      patternState = ANXIETY;
    }
  }
}



void playPattern() {

  if (patternState == ANGRY && millis() > enterStateTimer + 3000) {
    canChange = true;
    patternState = NONE;
    // lastState = ANGRY;
  }

  if (patternState == HAPPY && millis() > enterStateTimer + 7000) {
    canChange = true;
    patternState = NONE;
    // lastState = HAPPY;
  }

  if (patternState == ANXIETY && millis() > enterStateTimer + 3000) {
    canChange = true;
    patternState = NONE;
  }

  switch (patternState) {
    case NONE:
      patternNone();
      break;
    case ANGRY:
      patternAngry();
      break;
    case HAPPY:
      patternHappy();
      break;
    case ANXIETY:
      patternAnxiety();
      break;
  }
}

void lessLight() {
  if (lightValue == minLight) return;
  lightValue--;
}

void moreLight() {
  if (lightValue == maxLight) return;
  lightValue++;
}

void debug() {
  if (patternState == NONE) {
    Serial.print("NONE!");
    patternNone();

  } else if (patternState == ANGRY) {
    Serial.print("ANGRY!");
    patternAngry();

  } else if (patternState == HAPPY) {
    Serial.print("HAPPY!");
    patternHappy();
  }

  Serial.print(" - " + String(patternState) + " - canChange: " + canChange + " - timer:" + enterStateTimer);
  Serial.println();
}
