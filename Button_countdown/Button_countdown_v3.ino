// Voor deze opdracht is gebruik gemaakt van het voorbeeld 
// met een LED en een knop uit de slides van Edwin van Ouwerkerk-Moria, werkcollege 2. 
// https://gi1819.hku.nl/wp-content/uploads/2018/12/ITTT-Werkcollege-12-Blink-and-youll-miss-it-Meten-is-weten.pdf

#include <Servo.h>

int countdown = 0;
int setTime = 750;

int lampCutOff_5;
int lampCutOff_4;
int lampCutOff_3;
int lampCutOff_2;
int lampCutOff_1;

bool opened = false;
bool resettingCountdown = false;

// Servo
Servo servo1;
int servoClosed = 90;
int servoOpened = 0;
int servoPos;
int servoSpeed = 1;

void setup() {
  Serial.begin(9600);

  // Knop 1
  pinMode(3, INPUT);
  // Knop 2
  pinMode(4, INPUT);

  // Lampje 1
  pinMode(8, OUTPUT);
  // Lampje 2
  pinMode(9, OUTPUT);
  // Lampje 3
  pinMode(10, OUTPUT);
  // Lampje 4
  pinMode(11, OUTPUT);
  // Lampje 5
  pinMode(12, OUTPUT);
  // Lampje 6
  pinMode(2, OUTPUT);

  // Servo
  servo1.attach(6);

  // Lamp cutoff is based on the maximum time, and divided into 5 equal partitions
  lampCutOff_5 = setTime * 4 / 5;
  lampCutOff_4 = setTime * 3 / 5;
  lampCutOff_3 = setTime * 2 / 5;
  lampCutOff_2 = setTime * 1 / 5;
  lampCutOff_1 = setTime * 0 / 5;

  // Reset servo position
  servoPos = servoClosed;
  servo1.write(servoPos);
}

void loop() {
  delay(5);
  
  if (opened) {
    if (servoPos > servoOpened) {
      servoPos -= servoSpeed;
      servo1.write(servoPos);
      Serial.print(servoPos);
      Serial.print(" / ");
      Serial.println(servoOpened);
      Serial.println("Gate is opening!");
    } else {
      Serial.println("Gate has opened!");
    }
    return;
  }
  
  int buttonState1 = digitalRead(4);
  int buttonState2 = digitalRead(3);

//  Serial.print("Resetting countdown: ");
//  Serial.print(resettingCountdown);
//
//  Serial.print("  ||  Countdown: ");
//  Serial.println(countdown);

  if (resettingCountdown) {
    if (countdown < setTime) {
      countdown += 20;
    } else {
      resettingCountdown = false;
    }
  } else {
    if (buttonState1== 1) {
    resettingCountdown = true;
  } else if (countdown > 0) {
    countdown -= 1;
      if (buttonState2 == 1) {
        opened = true;
      }
    }
  }

  // When the gate is "opened", all leds light up, and the loop stops checking for the countdown
  if (opened) {
    digitalWrite(2, 1);
    digitalWrite(12, 1);
    digitalWrite(11, 1);
    digitalWrite(10, 1);
    digitalWrite(9, 1);
    digitalWrite(8, 1);
    return;
  }

  // Keep countdown below or equal to set time.
  if (countdown > setTime) {
    countdown = setTime;
  }
  // Check for each individual LED if it should be on. 
  if (countdown > lampCutOff_5) {
    digitalWrite(12, 1);
  } else {
    digitalWrite(12, 0);
  }
  if (countdown > lampCutOff_4) {
    digitalWrite(11, 1);
  } else {
    digitalWrite(11, 0);
  }
  if (countdown > lampCutOff_3) {
    digitalWrite(10, 1);
  } else {
    digitalWrite(10, 0);
  }
  if (countdown > lampCutOff_2) {
    digitalWrite(9, 1);
  } else {
    digitalWrite(9, 0);
  }
  if (countdown > lampCutOff_1) {
    digitalWrite(8, 1);
  } else {
    digitalWrite(8, 0);
  }
}
