void trust() {
  // for (int i = 0; i < 4; i++) {
  analogWrite(VIBRATOR, 75);
  delay(random(2000, 3000));

  analogWrite(VIBRATOR, 50);
  delay(random(800, 1200));
  // }
}

void joy() {
  analogWrite(VIBRATOR, POW_MED);
  delay(random(1000, 1300));

  analogWrite(VIBRATOR, 50);
  delay(random(200, 800));
}

void fear() {
  analogWrite(VIBRATOR, 250);
  delay(random(500, 800));

  analogWrite(VIBRATOR, 0);
  delay(random(1000, 1800));
}

void joy2() {
  analogWrite(VIBRATOR, 50);
  delay(random(2000, 3500));

  analogWrite(VIBRATOR, 100);
  delay(random(600, 1200));
}