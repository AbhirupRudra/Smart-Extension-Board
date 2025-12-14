#define RELAY1 14
#define RELAY2 12
#define RELAY3 13
#define RELAY4 15

#define BTN1 5
#define BTN2 4
#define BTN3 0
#define BTN4 2

const int btnPins[4] = { BTN1, BTN2, BTN3, BTN4 };
const int relayPins[4] = { RELAY1, RELAY2, RELAY3, RELAY4 };

bool relayState[4] = { 0, 0, 0, 0 };
bool lastStableState[4] = { HIGH, HIGH, HIGH, HIGH };
bool lastReading[4] = { HIGH, HIGH, HIGH, HIGH };

unsigned long lastDebounceTime[4] = { 0, 0, 0, 0 };
const unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(btnPins[i], INPUT_PULLUP);
  }
}

void loop() {
  unsigned long currentTime = millis();
  for (int i = 0; i < 4; i++) {
    bool reading = digitalRead(btnPins[i]);
    if (reading != lastReading[i]) {
      lastDebounceTime[i] = currentTime;
      lastReading[i] = reading;
    }
    if ((currentTime - lastDebounceTime[i]) > debounceDelay) {
      if (reading != lastStableState[i]) {
        lastStableState[i] = reading;
        if (reading == LOW) {
          relayState[i] = !relayState[i];
          digitalWrite(relayPins[i], relayState[i] ? LOW : HIGH);
          Serial.print("Plug ");
          Serial.print(i + 1);
          Serial.print(" -> ");
          Serial.println(relayState[i] ? "ON" : "OFF");
        }
      }
    }
  }
}
