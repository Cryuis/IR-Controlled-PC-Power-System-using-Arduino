# Arduino IR Remote PC Power Switch

## Project Overview

This project enables a computer to be powered on using an infrared (IR) remote control. An Arduino Uno receives the IR signal and activates a relay module that simulates pressing the PC’s physical power button.

The system is designed to trigger a single power-on action when a specific button on the IR remote is pressed.

---

## Components Used

* Arduino Uno
* IR Receiver Module
* IR Remote Controller
* 5V Relay Module
* Jumper Wires

---

## Library Used

* DIYables_IRcontroller

---

## System Operation

1. The IR receiver detects input from the remote control.
2. When the designated button (OK) is pressed, the Arduino activates the relay.
3. The relay briefly closes the circuit connected to the PC motherboard’s power switch pins.
4. This simulates a physical button press and powers on the computer.
5. The relay is released after the button is no longer pressed.

---

## Pin Configuration

| Component    | Arduino Pin |
| ------------ | ----------- |
| IR Receiver  | Pin 2       |
| Relay Module | Pin 3       |

---

## Arduino Code

```cpp
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
  digitalWrite(ZAP, LOW);
}

void loop() {
  Key17 currentKey = irController.getKey();

  if ((int)currentKey == KEY17_OK) {
    if (!relayOn) {
      pressStart = millis();
      relayOn = true;
      digitalWrite(ZAP, HIGH);
    }
  } else {
    if (relayOn) {
      digitalWrite(ZAP, LOW);
      relayOn = false;
    }
  }

  delay(50);
}
```

---

## Code Description

The program continuously reads input from the IR receiver. When the OK button on the remote is detected, the relay is activated, simulating a press of the PC power button. Once the button is released, the relay is deactivated.

---

## Demo Video

### Test 1
[![Demo 1](https://img.youtube.com/vi/m-KyTwU8WNY/0.jpg)](https://youtube.com/shorts/m-KyTwU8WNY)

### Test 2
[![Demo 2](https://img.youtube.com/vi/a0I4rgG8QAY/0.jpg)](https://youtube.com/shorts/a0I4rgG8QAY)

---

## Notes

* Ensure correct connection of the relay module to the motherboard power switch pins.
* Verify that the IR remote button code matches `KEY17_OK`.
* Adjust wiring and placement of the IR receiver for reliable signal detection.

---

## Authors

* Cavero Cyrus
* Regindin Sean
