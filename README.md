# ArduinoWithJavaSpringBoot

Ett skolprojekt som visar hur man kan integrera valfri IoT-enhet (i det här fallet Arduino och ESP32) med en  
Java Spring Boot-backend för att skicka och ta emot data.

## Innehåll

- `Arduino` – Arduino-skisser/kod för att läsa sensorvärden och kommunicera med servern via serieport  
- `ESP32` – kod för ESP32-modulen för att läsa och skicka sensorvärden via Wi-Fi  
- `JavaSpringBoot` – Spring Boot-applikation som exponerar REST-API och hanterar data  
- `.vscode` – inställningar för Visual Studio Code  
- `platformio.ini` – konfigurationsfil för PlatformIO  
- `.gitignore` – filer och mappar som ska ignoreras av Git

## Funktioner

- Arduino / ESP32: läser sensorvärden (t.ex. temperatur, fuktighet etc.)  
- Skickar data via HTTP till Spring Boot-servern  
- Backend: tar emot data, lagrar det i en MySQL-databas samt exponerar API-slutpunkter för frontend (thymeleaf)  
- Enkel struktur för att demonstrera IoT-arkitektur med mikrocontroller + modern backend

## Förutsättningar

Innan du kör projektet behöver du:

- Java Development Kit (JDK) + Maven (t.ex. via IntelliJ IDEA)  
- PlatformIO för att flasha Arduino/ESP32-koden (t.ex via Visual Studio Code)
- MySQL Server för att lagra data (t.ex. via MySQL Workbench) 

