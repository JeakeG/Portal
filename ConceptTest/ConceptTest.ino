/*   
 *   ConceptTest
 *   
 *   The purpose of this sketch is to test team Portal's concept design.
 *   It will consist of having the an arduino communicate with a motor driver so that a stepper
 *   motor will be controlled within by two buttons.
 *   
 *   Created 18 Feb 2021
 *   Jake Guidry
 *   Modified 19 Feb 2021
 *   Jake Guidry *It work now*
 *   
 *   https://github.com/JeakeG/Portal
 *   
 *   Driver Connections
 *   PU+ => 5V
 *   PU- => 11
 *   
 *   DR+ => 5V
 *   DI- => 13
 *   
 *   Run Button attaches to pin 3 and ground
 *   Dir Button attaches to pin 2 and ground
 *   
 *   Pot attaches to +5V, pin A0, and ground
 */ 

int const PUL_PIN = 11;
int const DIR_PIN = 13;
int const GO_READ_PIN = 3;
int const DIR_READ_PIN = 2;
int const POT_PIN = A0;

bool shouldGo = false;

int long last_go_interrupt = 0;
int long last_dir_interrupt = 0;

void setup() {
  pinMode(PUL_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  pinMode(GO_READ_PIN, INPUT_PULLUP);
  pinMode(DIR_READ_PIN, INPUT_PULLUP);

  digitalWrite(DIR_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(GO_READ_PIN), toggleRunning, RISING);
  attachInterrupt(digitalPinToInterrupt(DIR_READ_PIN), toggleDirection, RISING);

  Serial.begin(9600);
}

void loop() {
  if (shouldGo) {
    int time = map(analogRead(POT_PIN), 0, 1023, 1, 1000);
    digitalWrite(PUL_PIN, HIGH);
    delayMicroseconds(time);
    digitalWrite(PUL_PIN, LOW);
    delayMicroseconds(time);
  } else {
    delay(1);
  }
}

void toggleRunning() {
  long time = millis();
  if (time - last_go_interrupt > 200) {
    shouldGo = !shouldGo;
    if (shouldGo) {
      Serial.println("Running: True");
    } else {
      Serial.println("Running: False");
    }
  }
  last_go_interrupt = time;
}

void toggleDirection() {
  long time = millis();
  if (time - last_dir_interrupt > 200) {
    digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));
    if (digitalRead(DIR_PIN)) {
      Serial.println("Direction: 1");
    } else {
      Serial.println("Direction: 0");
    }
  }
  last_dir_interrupt = time;
}
