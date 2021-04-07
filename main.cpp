#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

/*MOTION DETECTION*/
#define TAP_THRESHOLD 10
bool tapDetected;

/*LED ON/OFF*/
//default state is off
bool turnON = false; 
bool turnOFF = true; 

/*Color Sensor Variables*/
uint8_t red, green, blue;

void activate() {
  if (turnOFF) {
    //toggle state
    turnOFF = false;
    turnON = true;
    //if LED is off, turn it on
    for (int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i, red, green, blue);
    }
  }
  else if (turnON) {
    //toggle state
    turnOFF = true;
    turnON = false;
    //if LED is off, turn it on
    CircuitPlayground.clearPixels();
  }
}

void setCustom() {
  Serial.println("Place object near sensor to read color");
  
  CircuitPlayground.clearPixels();

  // Now take a color reading (the red, green, blue color components will be
  // returned in the parameters passed in).
  CircuitPlayground.senseColor(red, green, blue);

  // Gamma correction makes LED brightness appear more linear
  red = CircuitPlayground.gamma8(red);
  green = CircuitPlayground.gamma8(green);
  blue = CircuitPlayground.gamma8(blue);

  // flash pixels to show it has been read
  for (int i=0; i<10; ++i) {
    CircuitPlayground.strip.setPixelColor(i, red, green, blue);
  }

  CircuitPlayground.clearPixels();
}

void setup() {
  //establish tap interrupt
  CircuitPlayground.begin();

  CircuitPlayground.setBrightness(255);

  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  
  //detect both single and double taps
  CircuitPlayground.setAccelTap(2, TAP_THRESHOLD); 

  turnOFF = false;
  
  setCustom();

  attachInterrupt(digitalPinToInterrupt(7), activate, FALLING);
}

void loop() {

}