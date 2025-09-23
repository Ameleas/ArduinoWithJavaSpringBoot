#include <Arduino.h>

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
  float voltage = tmpReading * (5.0 / 1023.0); // om 5V referens
  float temperatureC = (voltage - 0.5) * 100.0; // TMP36 formel

  // Läs LDR
  int light = analogRead(LDR_PIN);

  Serial.print("{\"temp\":");
  Serial.print(temperatureC);
  Serial.print(",\"light\":");
  Serial.print(light);
  Serial.println("}");

  // Enkel logik för färg:
  if (light < 200) { // mörkt
    analogWrite(LED_RED, 255);  // rött
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 0);
  } else if (temperatureC < 18) { // kallt
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 255); // blått
  } else {
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 255); // grönt = allt okej
    analogWrite(LED_BLUE, 0);
  }

  delay(1000);
}