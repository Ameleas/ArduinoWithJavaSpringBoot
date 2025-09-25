#include <Arduino.h>

#define LED_RED 9
#define LED_GREEN 10
#define LED_BLUE 11


void tooDark(int led1, int led2, int led3) {
  analogWrite(led1, 255); // Red light on
  analogWrite(led2, 0);
  analogWrite(led3, 0);
}

void tooCold(int led1, int led2, int led3) {
  analogWrite(led1, 0);
  analogWrite(led2, 0);
  analogWrite(led3, 255); // Blue light on
}

void allGood(int led1, int led2, int led3) {
  analogWrite(led1, 0);
  analogWrite(led2, 255); // Green light on
  analogWrite(led3, 0);
}

void analyzeSensorData(float temperature, int light) {
  if (light < 200) { // mörkt
    tooDark(LED_RED, LED_GREEN, LED_BLUE);
  } else if (temperature < 18) {
    tooCold(LED_RED, LED_GREEN, LED_BLUE);
  } else {
    allGood(LED_RED, LED_GREEN, LED_BLUE);
  }
}

void tooSerialMonitor(float temperatureC, int light) {
  Serial.print("{\"temp\":");
  Serial.print(temperatureC);
  Serial.print(",\"light\":");
  Serial.print(light);
  Serial.println("}");

}