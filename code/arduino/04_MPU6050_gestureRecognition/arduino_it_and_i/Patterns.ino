void patternNone() {
  analogWrite(VIBRATOR, 0);
  delay(1);
}
void patternPoke() {
  analogWrite(VIBRATOR, POW_MED);
  delay(200);
  analogWrite(VIBRATOR, 0);
  delay(500);
}

void patternAngry() {
  analogWrite(VIBRATOR, POW_HIGH);
  delay(random(500, 750));
  analogWrite(VIBRATOR, 0);
  delay(100);
}

void patternHappy() {

  if (happyRising) {
    happyValue += 8;
    happyValue %= 256;
    if (happyValue >= 255) happyRising = false;
  } else {
    happyValue -= 2;
    if (happyValue <= 50) happyRising = true;
  }
  analogWrite(VIBRATOR, happyValue);
  delay(10);
}

void patternFear() {
  analogWrite(VIBRATOR, POW_HIGH);
  delay(random(100, 750));

  analogWrite(VIBRATOR, POW_LOW);
  delay(random(750, 1250));

  analogWrite(VIBRATOR, 0);
}

int sadValue = POW_MED;
void patternSad() {
  sadValue -= random(1, 5);
  sadValue %= POW_MED + 1;
  if(sadValue <= 50) sadValue = POW_MED;
  analogWrite(VIBRATOR, sadValue);
  delay(50);
}

void patternAnxiety() {
  analogWrite(VIBRATOR, POW_LOW);
  delay(200);

  analogWrite(VIBRATOR, 0);
  delay(100);
}