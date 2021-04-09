#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

/*MOTION DETECTION*/
#define TAP_THRESHOLD 100

/*MOTION DETECTION*/
bool tapDetected;

/*LED ON/OFF*/
//default state is off
bool turnON = false; 
bool turnOFF = true; 

/*COLOR SENSOR*/
uint8_t red = 255;
uint8_t green = 255;
uint8_t blue = 255;

/*LIGHT PWM*/
int brightness;
int maxBright = 255;

void activate(); //function to turn on or off the device
void setCustom();//function to set a custom color for the lights
void adjustB();   //function to adjust the brightness of the LED based on room light

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  
  //establish tap interrupt
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  //detect both single and double taps
  CircuitPlayground.setAccelTap(2, TAP_THRESHOLD); 
  turnOFF = false;

  //attachInterrupt(digitalPinToInterrupt(CPLAY_LIS3DH_INTERRUPT), activate, FALLING);

  //ask user to set the custom color. default is white. 
  setCustom();
}

void loop() {
  adjustB();
}

void activate() {
  if (turnOFF) {
    //toggle state
    Serial.println("TAP");
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

void adjustB() {
  brightness = CircuitPlayground.lightSensor();
  //Serial.print("Sensor:"); Serial.print(brightness); Serial.print(",");
  //map the sensor value to a range the LED can accept. 
  brightness = map(brightness, 0, 1023, 0, maxBright);
  //invert the brightness because sensor and pixel should be inversly related
  brightness = map(brightness, 0, maxBright, maxBright, 0);
  //Serial.print("Pixel:"); Serial.println(brightness);

  //set the onboard LEDs to the pixel brightness
  CircuitPlayground.setBrightness(brightness);
  for (int i=0; i<10; i++){
    CircuitPlayground.setPixelColor(i, red, green, blue);
  }
}
