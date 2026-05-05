#include <DIYables_IRcontroller.h>

#define IR_RECEIVER 2
#define ZAP 3

DIYables_IRcontroller_17 irController(IR_RECEIVER, 200);

unsigned long pressStart = 0;
bool relayOn = false;

void setup() {
  Serial.begin(9600);
  irController.begin();
  pinMode(ZAP, OUTPUT);
  digitalWrite(ZAP, LOW);  // default OFF
}

void loop() {
  Key17 currentKey = irController.getKey();

  if ((int)currentKey == KEY17_OK) {
    if (!relayOn) {
      // First time button is detected
      pressStart = millis();
      relayOn = true;
      digitalWrite(ZAP, HIGH);
      Serial.println("Relay ON (button pressed)");
    }
  } else {
    if (relayOn) {
      // Button released, measure duration
      unsigned long pressDuration = millis() - pressStart;

      if (pressDuration < 1000) {
        Serial.println("Short press detected (power ON)");
      } else {
        Serial.println("Long press detected (power OFF)");
      }

      // Release relay
      digitalWrite(ZAP, LOW);
      relayOn = false;
      Serial.println("Relay OFF (button released)");
    }
  }

  delay(50);  // debounce
}
