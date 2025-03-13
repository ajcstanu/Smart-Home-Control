#include <WiFi.h>
#include <FirebaseESP32.h>
#include <PubSubClient.h>

// WiFi & MQTT Credentials
#define WIFI_SSID "your-ssid"
#define WIFI_PASSWORD "your-password"
#define MQTT_BROKER "your-mqtt-broker"
#define MQTT_TOPIC "home/automation"

// Firebase Credentials
#define FIREBASE_HOST "your-firebase-url"
#define FIREBASE_AUTH "your-firebase-secret"

WiFiClient espClient;
PubSubClient client(espClient);
FirebaseData firebaseData;

// Relays for appliances
const int relay1 = 5; // Light
const int relay2 = 18; // Fan

void callback(char *topic, byte *payload, unsigned int length); // Declare callback function

void setup() {
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);

    client.setServer(MQTT_BROKER, 1883);
    client.setCallback(callback);

    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);

    if (!client.connected()) {
        reconnect();
    }
}

void callback(char *topic, byte *payload, unsigned int length) {
    String message;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println("Message received: " + message);

    if (message == "light_on") {
        digitalWrite(relay1, HIGH);
        Firebase.setString(firebaseData, "/home/light", "ON");
    } else if (message == "light_off") {
        digitalWrite(relay1, LOW);
        Firebase.setString(firebaseData, "/home/light", "OFF");
    } else if (message == "fan_on") {
        digitalWrite(relay2, HIGH);
        Firebase.setString(firebaseData, "/home/fan", "ON");
    } else if (message == "fan_off") {
        digitalWrite(relay2, LOW);
        Firebase.setString(firebaseData, "/home/fan", "OFF");
    }
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32_Home_Automation")) {
            Serial.println("connected");
            client.subscribe(MQTT_TOPIC);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}