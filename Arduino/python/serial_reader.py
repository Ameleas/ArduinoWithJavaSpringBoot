import serial
import requests
import json
import time


ser = serial.Serial('COM6', 9600, timeout=1)

def get_latest_data():
    try:
        response = requests.get("http://localhost:8080/Dbsensor/Senast")
        if response.status_code == 200:
            latest = response.json()
            print("Senaste data från servern:")
            print(json.dumps(latest, indent=2, ensure_ascii=False))
        else:
            print("Kunde inte hämta senaste data. Statuskod:", response.status_code)
    except Exception as e:
        print("Fel vid hämtning av senaste data:", e)

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
    
