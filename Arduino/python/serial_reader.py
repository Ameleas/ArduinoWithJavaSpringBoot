import serial
import requests
import json
import time


ser = serial.Serial('COM6', 9600, timeout=1)

while True:
    try:
        line = ser.readline().decode('utf-8').strip()
        if line:
            print("Mottaget:", line)
            data = json.loads(line)  # Konvertera JSON-sträng till dict

              # Skapa payload enligt önskat format
            payload = {
                "id": 3,
                "device_type": "Arduino",
                "sensors": [
                    {
                        "sensor_reading": "temp",
                        "value": data["temp"]
                    },
                    {
                        "sensor_reading": "light",
                        "value": data["light"]
                    }
                ]
            }

            # Skicka till servern
            response = requests.post("http://localhost:8080/Dbsensor/addNewData", json=payload)

            print("Postat:", response.status_code)
    except Exception as e:
        print("Fel:", e)

    time.sleep(10)

    
