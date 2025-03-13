import paho.mqtt.client as mqtt
import firebase_admin
from firebase_admin import credentials, db
import os

# Firebase Setup
try:
    cred_path = "firebase-credentials.json" # Assumes credentials file is in the same directory
    if not os.path.exists(cred_path):
        raise FileNotFoundError(f"Firebase credentials file not found: {cred_path}")

    cred = credentials.Certificate(cred_path)
    firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://your-firebase-url.firebaseio.com/' # Replace with your firebase URL
    })
    print("Firebase initialized successfully.")
except FileNotFoundError as fnf_error:
    print(f"Error: {fnf_error}")
    exit(1) # Exit with an error code
except Exception as e:
    print(f"Error initializing Firebase: {e}")
    exit(1)

# MQTT Setup
MQTT_BROKER = "your-mqtt-broker" # Replace with your MQTT Broker address
MQTT_TOPIC = "home/automation"

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker")
        client.subscribe(MQTT_TOPIC)
    else:
        print(f"Failed to connect to MQTT broker, return code {rc}")

def on_message(client, userdata, msg):
    command = msg.payload.decode()
    print(f"Received command: {command}")

    try:
        if command == "light_on":
            db.reference("/home/light").set("ON")
        elif command == "light_off":
            db.reference("/home/light").set("OFF")
        elif command == "fan_on":
            db.reference("/home/fan").set("ON")
        elif command == "fan_off":
            db.reference("/home/fan").set("OFF")
        else:
            print(f"Unknown command: {command}")
    except Exception as e:
        print(f"Error updating Firebase: {e}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

try:
    client.connect(MQTT_BROKER, 1883, 60)
    client.loop_forever()
except Exception as e:
    print(f"Error connecting to MQTT broker: {e}")