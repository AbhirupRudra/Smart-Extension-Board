#define BLYNK_TEMPLATE_ID "TMPL3x4kIwojm"
#define BLYNK_TEMPLATE_NAME "SMART EXTENSION BOARD"
#define BLYNK_AUTH_TOKEN "MEnYBQxjPOrlRAEjUrrEZXj_2NaG2oGr"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ABHIRUP_RUDRA";
char pass[] = "12122006";

#define RELAY1 14
#define RELAY2 12
#define RELAY3 13
#define RELAY4 15

#define BTN1 5
#define BTN2 4
#define BTN3 0
#define BTN4 2

const int relayPins[4] = {RELAY1, RELAY2, RELAY3, RELAY4};
const int btnPins[4]   = {BTN1, BTN2, BTN3, BTN4};

bool relayState[4];
bool lastStableState[4] = {HIGH,HIGH,HIGH,HIGH};
bool lastReading[4]     = {HIGH,HIGH,HIGH,HIGH};

unsigned long lastDebounceTime[4] = {0,0,0,0};
const unsigned long debounceDelay = 50;

void saveState() {
  for(int i=0;i<4;i++) EEPROM.write(i, relayState[i]);
  EEPROM.commit();
}

void applyRelay(int i) {
  digitalWrite(relayPins[i], relayState[i] ? LOW : HIGH);
  Blynk.virtualWrite(i, relayState[i]);
}

void updateRelay(int i, int state) {
  relayState[i] = state;
  applyRelay(i);
  saveState();
}

BLYNK_WRITE(V0) { updateRelay(0, param.asInt()); }
BLYNK_WRITE(V1) { updateRelay(1, param.asInt()); }
BLYNK_WRITE(V2) { updateRelay(2, param.asInt()); }
BLYNK_WRITE(V3) { updateRelay(3, param.asInt()); }

BLYNK_CONNECTED() {
  Serial.println("Connected to Blynk");
  Blynk.syncAll();
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(10);

  for(int i=0;i<4;i++) relayState[i] = EEPROM.read(i);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Connecting to Blynk...");

  Blynk.config(auth);
  Blynk.connect();

  for(int i=0;i<4;i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], relayState[i] ? LOW : HIGH);
  }

  for(int i=0;i<4;i++) pinMode(btnPins[i], INPUT_PULLUP);

  for(int i=0;i<4;i++) Blynk.virtualWrite(i, relayState[i]);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi Lost! Reconnecting...");
    WiFi.begin(ssid, pass);
    delay(1000);
    return;
  }

  if (!Blynk.connected()) {
    Serial.println("Blynk Lost! Reconnecting...");
    Blynk.connect();
    return;
  }

  Blynk.run();

  unsigned long t = millis();
  for (int i = 0; i < 4; i++) {
    bool reading = digitalRead(btnPins[i]);
    if (reading != lastReading[i]) {
      lastDebounceTime[i] = t;
      lastReading[i] = reading;
    }
    if (t - lastDebounceTime[i] > debounceDelay) {
      if (reading != lastStableState[i]) {
        lastStableState[i] = reading;
        if (reading == LOW) {
          relayState[i] = !relayState[i];
          applyRelay(i);
          saveState();
          Serial.print("Relay ");
          Serial.print(i+1);
          Serial.print(" -> ");
          Serial.println(relayState[i]);
        }
      }
    }
  }
}
