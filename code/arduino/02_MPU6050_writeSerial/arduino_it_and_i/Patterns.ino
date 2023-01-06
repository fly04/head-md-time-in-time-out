#define VIBRATOR 9  // Analog output pin that the vibrator is attached to
#define POW_LOW 100
#define POW_MED 150
#define POW_HIGH 255

void patternAngry() {
  analogWrite(VIBRATOR, POW_HIGH);
  delay(500);
  analogWrite(VIBRATOR, 0);
  delay(100);
}