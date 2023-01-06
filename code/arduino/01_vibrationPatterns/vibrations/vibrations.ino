// These constants won't change. They're used to give names to the pins used:
#define VIBRATOR 9  // Analog output pin that the vibrator is attached to

enum PatternState { NONE,
                    POKE,
                    ANGRY,
                    HAPPY,
                    FEAR,
                    SAD,
                    ANXIETY };

PatternState patternState = NONE;

#define POW_LOW 100
#define POW_MED 150
#define POW_HIGH 255

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(VIBRATOR, OUTPUT);
}

void loop() {
  playPattern();
  switchPattern();
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
    case SAD: //endormi
      patternSad();
      break;
    case ANXIETY:
      patternAnxiety();
      break;
  }
}

void switchPattern() {
  while (Serial.available()) {
    int message = Serial.read();

    switch (message) {
      case 'N':
      case 'n':
        patternState = NONE;
        break;
      case 'p':
      case 'P':
        patternState = POKE;
        break;
      case 'a':
      case 'A':
        patternState = ANGRY;
        break;
      case 'h':
      case 'H':
        patternState = HAPPY;
        break;
      case 'f':
      case 'F':
        patternState = FEAR;
        break;
      case 's':
      case 'S':
        patternState = SAD;
        break;
      case 'x':
      case 'X':
        patternState = ANXIETY;
        break;
    }
  }
}
