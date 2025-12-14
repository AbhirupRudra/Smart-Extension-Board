#define BLYNK_TEMPLATE_ID "TMPL3x4kIwojm"
#define BLYNK_TEMPLATE_NAME "SMART EXTENSION BOARD"
#define BLYNK_AUTH_TOKEN "MEnYBQxjPOrlRAEjUrrEZXj_2NaG2oGr"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ABHIRUP_RUDRA";
char pass[] = "12122006";

// Relay / LED pins
#define R1 14
#define R2 12
#define R3 13
#define R4 15

void setup() {
  Serial.begin(115200);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  Serial.println("Connecting to Blynk...");
  Blynk.begin(auth, ssid, pass);
}

// Blynk buttons
BLYNK_WRITE(V0) { digitalWrite(R1, param.asInt() ? LOW : HIGH); }
BLYNK_WRITE(V1) { digitalWrite(R2, param.asInt() ? LOW : HIGH); }
BLYNK_WRITE(V2) { digitalWrite(R3, param.asInt() ? LOW : HIGH); }
BLYNK_WRITE(V3) { digitalWrite(R4, param.asInt() ? LOW : HIGH); }

void loop() {
  Blynk.run();
}
