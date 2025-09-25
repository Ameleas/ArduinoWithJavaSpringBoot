#include <Arduino.h>
#include "sensor.h"

#define TMP36_PIN A0
#define LDR_PIN A1
#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11

void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  // Läs TMP36
  int tmpReading = analogRead(TMP36_PIN);
  float voltage = tmpReading * (5.0 / 1023.0); // 5V referens
  float temperatureC = (voltage - 0.5) * 100.0; // TMP36 formel
  // Läs LDR
  int light = analogRead(LDR_PIN);

  analyzeSensorData(temperatureC, light);
  tooSerialMonitor(temperatureC, light);

  delay(1000);

}






  // Placeholder function for future sensor analysis