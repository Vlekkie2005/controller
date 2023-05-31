#define versie 1

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define D_UP                     9//~
#define D_DOWN                   10//~
#define D_LEFT                   8//~
#define D_RIGHT                  11//~

#define STICK_RX                 26//~
#define STICK_RY                 27//~

void setup() {
  Serial.begin(115200);

  pinMode(D_UP,     INPUT_PULLUP);
  pinMode(D_DOWN,     INPUT_PULLUP);
  pinMode(D_LEFT,     INPUT_PULLUP);
  pinMode(D_RIGHT,     INPUT_PULLUP);
}

void loop() {

  Serial.println(String(analogRead(STICK_RX)) + "," + String(analogRead(STICK_RY)) );
  delay(100);

  if(!digitalRead(D_UP)) {
    Serial.println("D_UP");
    delay(2000);
  }
  if(!digitalRead(D_DOWN)) {
    Serial.println("D_DOWN");
    delay(2000);
  }
  if(!digitalRead(D_LEFT)) {
    Serial.println("D_LEFT");
    delay(2000);
  }
  if(!digitalRead(D_RIGHT)) {
    Serial.println("D_RIGHT");
    delay(2000);
  }

}