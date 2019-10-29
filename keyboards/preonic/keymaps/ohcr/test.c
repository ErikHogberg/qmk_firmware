/*

#include <Mouse.h>

// set pin numbers for switch, joystick axes, and LED:
const int switchPin = 10;      // switch to turn on and off mouse control
const int mouseButton = 9;    // input pin for the mouse pushButton
const int xAxis = A0;         // joystick X axis
const int yAxis = A1;         // joystick Y axis
const int ledPin = 5;         // Mouse control LED

// parameters for reading the joystick:
int range = 18;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 8;    // resting threshold
int center = range / 2;       // resting position value

boolean mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state

void setup() {
  pinMode(switchPin, INPUT);       // the switch pin
  pinMode(ledPin, OUTPUT);         // the LED pin
}

void loop() {
  // read the switch:
  int switchState = digitalRead(switchPin);
  // if it's changed and it's high, toggle the mouse state:
  if (switchState != lastSwitchState) {
    if (switchState == HIGH) {
      mouseIsActive = !mouseIsActive;
      // turn on LED to indicate mouse state:
      digitalWrite(ledPin, mouseIsActive);
    }
  }
  // save switch state for next comparison:
  lastSwitchState = switchState;

  // read and scale the two axes:
  int xReading = readAxis(A0);
  int yReading = readAxis(A1);

  // if the mouse control state is active, move the mouse:
  if (mouseIsActive) {
    Mouse.move(xReading, yReading, 0);
  }

  // read the mouse button and click or not click:
  // if the mouse button is pressed:
  if (digitalRead(mouseButton) == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
  
  delay(responseDelay);
}


//  reads an axis (0 or 1 for x or y) and scales the analog input range to a range
//  from 0 to <range>


int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  if (thisAxis==A0) {
    distance = distance * -1;
  }

  // return the distance for this axis:
  return distance;
}

//

#include "champ40j.h"
#include "analog.c"
#include "math.h"
#include "pincontrol.h"
#include "pointing_device.h"
#include "print.h"
#include "report.h"
#include "timer.h"

// Joystick
// Set Pins
int xPin = 3; // VRx
int yPin = 2; // VRy
int swPin = C4; // SW

// Set Parameters
int minAxisValue = 0;
int maxAxisValue = 1023;

int maxCursorSpeed = 1;

int xPolarity = 1;
int yPolarity = -1;

int cursorTimeout = 10;

int xOrigin, yOrigin;

uint16_t lastCursor = 0;

int axisCoordinate(int pin, int origin) {
  int direction;
  int distanceFromOrigin;
  int range;

  int position = analogRead(pin);

  if (origin == position) {
    return 0;
  } else  if (origin > position) {
    distanceFromOrigin = origin - position;
    range = origin - minAxisValue;
    direction = -1;
  } else {
    distanceFromOrigin = position - origin;
    range = maxAxisValue - origin;
    direction = 1;
  }

  float percent = (float)distanceFromOrigin / range;
    int coordinate = (int)(percent * 100);
    if (coordinate < 0) {
      return 0;
    }
    else if (coordinate > 100) {
      return 100 * direction;
    }
    else {
      return coordinate * direction;
    }
}

int axisToMouseComponent(int pin, int origin, int maxSpeed, int polarity) {
  int coordinate = axisCoordinate(pin, origin);
  print_decs(coordinate); println();
  if (coordinate == 0) {
    return 0;
  }
  else {
    float percent = (float)coordinate / 100;
    return percent * maxCursorSpeed * polarity * (abs(coordinate)/6);
  }
}

void pointing_device_task(void) {
  report_mouse_t report;
  report.x = 0;
  report.y = 0;
  report.h = 0;
  report.v = 0;
  report.buttons = 0;

  // todo read as one vector
  if (timer_elapsed(lastCursor) > cursorTimeout) {
    lastCursor = timer_read();
    report.x = axisToMouseComponent(xPin, xOrigin, maxCursorSpeed, xPolarity);
    report.y = axisToMouseComponent(yPin, yOrigin, maxCursorSpeed, yPolarity);
  }

  if (digitalRead(swPin) == 1) {
    report.buttons |= MOUSE_BTN1;
  }

  pointing_device_set_report(report);
  pointing_device_send();
}

void matrix_init_kb(void) {
  timer_init();
  xOrigin = analogRead(xPin);
  yOrigin = analogRead(yPin);
}

//

int maxCursorSpeed = 4;
int precisionSpeed = 1;
int speedRegulator = 20; // Lower Values Create Faster Movement

int axisToMouseComponent(int pin, int origin, int maxSpeed, int polarity) {
  int coordinate = axisCoordinate(pin, origin);
  if (coordinate == 0) {
    return 0;
  }
  else {
    float percent = (float)coordinate / 100;
    if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
      return percent * precisionSpeed * polarity * (abs(coordinate)/speedRegulator);
    }
    else {
      return percent * maxCursorSpeed * polarity * (abs(coordinate)/speedRegulator);
    }
  }
}

//

// #include "champ40j.h"
#include "analog.c"
#include "math.h"
#include "pincontrol.h"
#include "pointing_device.h"
#include "print.h"
#include "report.h"
#include "timer.h"

// Joystick
// Set Pins
int xPin = 3; // VRx
int yPin = 2; // VRy
int swPin = C4; // SW

// Set Parameters
int minAxisValue = 0;
int maxAxisValue = 1023;

//int maxCursorSpeed = 1;

int maxCursorSpeed = 4;
int precisionSpeed = 1;
int speedRegulator = 20; // Lower Values Create Faster Movement

int xPolarity = 1;
int yPolarity = -1;

int cursorTimeout = 10;

int xOrigin, yOrigin;

uint16_t lastCursor = 0;

int axisCoordinate(int pin, int origin) {
  int direction;
  int distanceFromOrigin;
  int range;

  int position = analogRead(pin);

  if (origin == position) {
    return 0;
  } else  if (origin > position) {
    distanceFromOrigin = origin - position;
    range = origin - minAxisValue;
    direction = -1;
  } else {
    distanceFromOrigin = position - origin;
    range = maxAxisValue - origin;
    direction = 1;
  }

  float percent = (float)distanceFromOrigin / range;
    int coordinate = (int)(percent * 100);
    if (coordinate < 0) {
      return 0;
    }
    else if (coordinate > 100) {
      return 100 * direction;
    }
    else {
      return coordinate * direction;
    }
}

int axisToMouseComponent(int pin, int origin, int maxSpeed, int polarity) {
  int coordinate = axisCoordinate(pin, origin);
  if (coordinate == 0) {
    return 0;
  }
  else {
    float percent = (float)coordinate / 100;
    if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
      return percent * precisionSpeed * polarity * (abs(coordinate)/speedRegulator);
    }
    else {
      return percent * maxCursorSpeed * polarity * (abs(coordinate)/speedRegulator);
    }
  }
}

void pointing_device_task(void) {
  report_mouse_t report;
  report.x = 0;
  report.y = 0;
  report.h = 0;
  report.v = 0;
  report.buttons = 0;

  // todo read as one vector
  if (timer_elapsed(lastCursor) > cursorTimeout) {
    lastCursor = timer_read();
    report.x = axisToMouseComponent(xPin, xOrigin, maxCursorSpeed, xPolarity);
    report.y = axisToMouseComponent(yPin, yOrigin, maxCursorSpeed, yPolarity);
  }

  if (digitalRead(swPin) == 1) {
    report.buttons |= MOUSE_BTN1;
  }

  pointing_device_set_report(report);
  pointing_device_send();
}

void matrix_init_kb(void) {
  timer_init();
  xOrigin = analogRead(xPin);
  yOrigin = analogRead(yPin);
}
// */
