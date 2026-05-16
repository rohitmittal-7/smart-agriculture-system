#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include "DHT.h"

//================== WiFi ==================//
#define WIFI_SSID "OnePlus Nord CE4"
#define WIFI_PASSWORD "1234554321"

//================== Firebase ==================//
#define DATABASE_URL "https://smart-agriculture-7888c-default-rtdb.asia-southeast1.firebasedatabase.app/"
const char* FIREBASE_SECRET = "8yfvQ2MlgDVXQUpoiC71yj0G4WrMdnxs1DT1RXHQ";

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

//================== DHT Sensor ==================//
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//================== Moisture Sensor ==================//
#define MOISTURE_PIN A0

//================== Pump Relay ==================//
#define RELAY_PIN D1   // connect relay control to D1

//================== Pump Control Variables ==================//
String pumpMode = "AUTO";   // "AUTO" or "MANUAL"
String pumpStatus = "OFF";
int moistureValue = 0;
float temperature = 0;
float humidity = 0;

// Moisture threshold for automatic mode
const int MOISTURE_THRESHOLD = 500;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  dht.begin();

  // Connect WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n✅ WiFi connected: " + WiFi.localIP().toString());

  // Firebase config
  config.database_url = DATABASE_URL;
  auth.token.uid = "";
  config.signer.tokens.legacy_token = FIREBASE_SECRET;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("✅ Firebase Ready!");

  // Initialize Firebase pump/mode data if not exist
  if (!Firebase.getString(fbdo, "/pump/mode")) {
    Firebase.setString(fbdo, "/pump/mode", "AUTO");
  }
  if (!Firebase.getString(fbdo, "/pump/status")) {
    Firebase.setString(fbdo, "/pump/status", "OFF");
  }
}

void loop() {

  //=== Read Sensors ===//
  moistureValue = analogRead(MOISTURE_PIN);
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  //=== Send sensor data to Firebase ===//
  if (Firebase.setInt(fbdo, "/sensors/moisture", moistureValue))
    Serial.println("Moisture sent: " + String(moistureValue));

  if (Firebase.setFloat(fbdo, "/sensors/temperature", temperature))
    Serial.println("Temperature sent: " + String(temperature));

  if (Firebase.setFloat(fbdo, "/sensors/humidity", humidity))
    Serial.println("Humidity sent: " + String(humidity));

  //=== Read Pump Mode from Firebase ===//
  if (Firebase.getString(fbdo, "/pump/mode")) {
    pumpMode = fbdo.stringData();
  }

  //==================== Pump Control ====================//
  if (pumpMode == "AUTO") {

    // Automatic: control based on moisture
    if (moistureValue > MOISTURE_THRESHOLD) {
      pumpStatus = "ON";
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      pumpStatus = "OFF";
      digitalWrite(RELAY_PIN, LOW);
    }

    Firebase.setString(fbdo, "/pump/status", pumpStatus);
  }

  else if (pumpMode == "MANUAL") {

    // Manual: read status from Firebase (buttons)
    if (Firebase.getString(fbdo, "/pump/status")) {
      String manualStatus = fbdo.stringData();
      pumpStatus = manualStatus;

      if (pumpStatus == "ON") {
        digitalWrite(RELAY_PIN, HIGH);
      } else {
        digitalWrite(RELAY_PIN, LOW);
      }
    }
  }

  delay(2000);  // 2 seconds delay
}
