#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 6, 5, 4, 3, 2);

// =====================================================
// ROAD 1
// =====================================================
int R1 = 7;
int Y1 = 9;
int G1 = 11;

// =====================================================
// ROAD 2
// =====================================================
int R2 = 12;
int Y2 = 13;
int G2 = A0;

// =====================================================
// BUTTONS
// =====================================================
int pedButton = A2;

int ambBtn1 = 10;
int ambBtn2 = 1;

// =====================================================
// BUZZER
// =====================================================
int buzzer = A1;

// =====================================================
// HC-SR04 SENSOR 1
// =====================================================
int trig1 = A3;
int echo1 = A4;

// =====================================================
// HC-SR04 SENSOR 2
// =====================================================
int trig2 = 0;
int echo2 = A5;

// =====================================================
// FLAGS
// =====================================================
bool pedRequest = false;

// =====================================================
// ALL LIGHTS OFF
// =====================================================
void allLightsOff() {

  digitalWrite(R1, LOW);
  digitalWrite(Y1, LOW);
  digitalWrite(G1, LOW);

  digitalWrite(R2, LOW);
  digitalWrite(Y2, LOW);
  digitalWrite(G2, LOW);
}

// =====================================================
// BUZZER
// =====================================================
void beep() {

  tone(buzzer, 2000);

  delay(150);

  noTone(buzzer);
}

// =====================================================
// LCD
// =====================================================
void showLCD(String l1, String l2) {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(l1);

  lcd.setCursor(0,1);
  lcd.print(l2);
}

// =====================================================
// DISTANCE FUNCTION
// =====================================================
long getDistance(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  long distance = duration * 0.034 / 2;

  delay(50);

  return distance;
}

// =====================================================
// IDLE MODE
// =====================================================
void idleYellowMode() {

  while (true) {

    long d1 = getDistance(trig1, echo1);
    long d2 = getDistance(trig2, echo2);

    // Vehicle detected
    if ((d1 < 60 && d1 > 0) ||
        (d2 < 60 && d2 > 0)) {

      allLightsOff();
      return;
    }

    // BOTH YELLOW BLINK

    allLightsOff();

    digitalWrite(Y1, HIGH);
    digitalWrite(Y2, HIGH);

    lcd.setCursor(0,0);
    lcd.print("NO VEHICLES  ");

    lcd.setCursor(0,1);
    lcd.print("IDLE MODE    ");

    delay(500);

    allLightsOff();

    delay(500);
  }
}

// =====================================================
// CONTINUOUS SENSOR CHECK
// =====================================================
void checkIdleMode() {

  long d1 = getDistance(trig1, echo1);
  long d2 = getDistance(trig2, echo2);

  // BOTH roads empty
  if ((d1 > 60 || d1 == 0) &&
      (d2 > 60 || d2 == 0)) {

    idleYellowMode();
  }
}

// =====================================================
// CHECK PEDESTRIAN
// =====================================================
void checkPedestrian() {

  if (digitalRead(pedButton) == LOW) {

    pedRequest = true;
  }
}

// =====================================================
// PEDESTRIAN MODE
// =====================================================
void pedestrianMode() {

  // BOTH RED

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);

  showLCD("PEDESTRIAN", "WAIT");

  delay(1000);

  // R1 RED | R2 GREEN

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(G2, HIGH);

  showLCD("PEDESTRIAN", "CROSS NOW");

  for (int i = 5; i >= 0; i--) {

    checkIdleMode();

    lcd.setCursor(12,1);

    lcd.print(i);
    lcd.print(" ");

    beep();

    delay(700);
  }

  // R2 YELLOW

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(Y2, HIGH);

  showLCD("PEDESTRIAN", "ENDING");

  delay(2000);

  // BOTH RED

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);

  delay(1000);

  pedRequest = false;
}

// =====================================================
// AMBULANCE MODE
// =====================================================
void ambulanceManual() {

  while (digitalRead(ambBtn1) == LOW ||
         digitalRead(ambBtn2) == LOW) {

    checkIdleMode();

    allLightsOff();

    // ROAD1 AMBULANCE
    if (digitalRead(ambBtn1) == LOW) {

      digitalWrite(G1, HIGH);
      digitalWrite(R2, HIGH);

      showLCD("AMBULANCE ->", "R1 >>> GO");
    }

    // ROAD2 AMBULANCE
    else if (digitalRead(ambBtn2) == LOW) {

      digitalWrite(R1, HIGH);
      digitalWrite(G2, HIGH);

      showLCD("AMBULANCE <-", "R2 <<< GO");
    }
  }

  // BOTH YELLOW

  allLightsOff();

  digitalWrite(Y1, HIGH);
  digitalWrite(Y2, HIGH);

  beep();

  showLCD("SWITCHING", "YELLOW");

  delay(2000);

  // BOTH RED

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);

  delay(1000);
}

// =====================================================
// SETUP
// =====================================================
void setup() {

  lcd.begin(16,2);

  // ROAD1
  pinMode(R1, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(G1, OUTPUT);

  // ROAD2
  pinMode(R2, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(G2, OUTPUT);

  // BUTTONS
  pinMode(pedButton, INPUT_PULLUP);

  pinMode(ambBtn1, INPUT_PULLUP);
  pinMode(ambBtn2, INPUT_PULLUP);

  // BUZZER
  pinMode(buzzer, OUTPUT);

  // SENSOR1
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  // SENSOR2
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  showLCD("SMART TRAFFIC", "STARTING...");

  delay(2000);

  lcd.clear();
}

// =====================================================
// MAIN LOOP
// =====================================================
void loop() {

  // CONTINUOUS SENSOR CHECK
  checkIdleMode();

  // =================================================
  // PHASE 1
  // R1 RED | R2 GREEN
  // =================================================

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(G2, HIGH);

  for (int i = 10; i >= 0; i--) {

    checkIdleMode();

    if (digitalRead(ambBtn1) == LOW ||
        digitalRead(ambBtn2) == LOW) {

      ambulanceManual();
      return;
    }

    checkPedestrian();

    if (pedRequest) {

      pedestrianMode();
      return;
    }

    lcd.setCursor(0,0);
    lcd.print("R2 GREEN     ");

    lcd.setCursor(0,1);
    lcd.print("Time: ");

    lcd.print(i);

    lcd.print("s   ");

    delay(1000);
  }

  // =================================================
  // PHASE 2
  // R1 RED | R2 YELLOW
  // =================================================

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(Y2, HIGH);

  beep();

  showLCD("R2 YELLOW", "WAIT");

  delay(2000);

  // =================================================
  // PHASE 3
  // BOTH RED
  // =================================================

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);

  showLCD("ALL RED", "STOP");

  delay(1000);

  // =================================================
  // PHASE 4
  // R1 YELLOW | R2 RED
  // =================================================

  allLightsOff();

  digitalWrite(Y1, HIGH);
  digitalWrite(R2, HIGH);

  beep();

  showLCD("R1 YELLOW", "READY");

  delay(2000);

  // =================================================
  // PHASE 5
  // R1 GREEN | R2 RED
  // =================================================

  allLightsOff();

  digitalWrite(G1, HIGH);
  digitalWrite(R2, HIGH);

  for (int i = 10; i >= 0; i--) {

    checkIdleMode();

    if (digitalRead(ambBtn1) == LOW ||
        digitalRead(ambBtn2) == LOW) {

      ambulanceManual();
      return;
    }

    checkPedestrian();

    if (pedRequest) {

      pedestrianMode();
      return;
    }

    lcd.setCursor(0,0);
    lcd.print("R1 GREEN     ");

    lcd.setCursor(0,1);
    lcd.print("Time: ");

    lcd.print(i);

    lcd.print("s   ");

    delay(1000);
  }

  // =================================================
  // PHASE 6
  // R1 YELLOW | R2 RED
  // =================================================

  allLightsOff();

  digitalWrite(Y1, HIGH);
  digitalWrite(R2, HIGH);

  beep();

  showLCD("R1 YELLOW", "WAIT");

  delay(2000);

  // =================================================
  // PHASE 7
  // BOTH RED
  // =================================================

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);

  showLCD("ALL RED", "STOP");

  delay(1000);

  // =================================================
  // PHASE 8
  // R1 RED | R2 YELLOW
  // =================================================

  allLightsOff();

  digitalWrite(R1, HIGH);
  digitalWrite(Y2, HIGH);

  beep();

  showLCD("R2 YELLOW", "READY");

  delay(2000);
}
