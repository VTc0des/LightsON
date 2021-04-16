#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

/*MOTION DETECTION
  #define TAP_THRESHOLD 100
  bool tapDetected;*/

/*LED ON/OFF*/
//default state is off
bool isON = false;
bool isOFF = true;
bool left = false;
bool right = false;

/*COLOR SENSOR*/
//DEFAULT VALUE IS WHITE
uint8_t red = 255;
uint8_t green = 255;
uint8_t blue = 255;

/*LIGHT PWM*/
int brightness;
int maxBright = 255;

/*FUNCTION DECLARATIONS*/
void activate();      //function to turn on or off the device
void setCustom();     //function to set a custom color for the lights
void adjustMaxB();    //function for user to tap capacitive touch pads to set maximum brightness.
void button();        //function to turn ON or OFF all circuit playground
void modusOperandi(); //function to toggle mode from standard to fireplace
void fireplace();
void adjustB();       //function to adjust the brightness of the LED based on room light
void allLEDs();       //function to turn on all the LEDs.

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();

  //turn ON the LEDs the moment the circuit is connected to power.
  activate();

  //ask user to set the custom color. default is white.
  setCustom();

  /*AccelTap Section - DOES NOT WORK
    //establish tap interrupt
    //CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
    //detect both single and double taps
    //CircuitPlayground.setAccelTap(2, TAP_THRESHOLD);
    //attachInterrupt(digitalPinToInterrupt(CPLAY_LIS3DH_INTERRUPT), activate, FALLING);
  */
}

void loop() {
  button();        //check for button push left - ON/OFF, right - change color
  modusOperandi(); //check for slide switch status, switch position
  adjustMaxB ();   //check for capacitive touch to adjust brightness of the LEDs
  adjustB();       //main function to auto-adjust LED brightness
}

void activate() {
  if (isOFF) {
    //toggle state
    isON = true;
    isOFF = false;
    //if LEDs are off, turn it on
    allLEDs();
  }
  else if (isON) {
    //toggle state
    isOFF = true;
    isON = false;
    //if LEDs are on, turn it off
    CircuitPlayground.clearPixels();
  }
}

void setCustom() {
  Serial.println("Place object near sensor to read color");

  CircuitPlayground.clearPixels();

  // Now take a color reading (the red, green, blue color components will be
  // returned in the parameters passed in).

  //if not button push wait for 5 seconds, grab the last instance?
  CircuitPlayground.senseColor(red, green, blue);

  //else if button push read immediately.

  // Gamma correction makes LED brightness appear more linear
  red = CircuitPlayground.gamma8(red);
  green = CircuitPlayground.gamma8(green);
  blue = CircuitPlayground.gamma8(blue);

  // flash pixels to show it has been read
  allLEDs();
}

void adjustMaxB() {
  //if slide switch is negative AND input is detected on EITHER touch pad
  //include serial print statements
  //if input is read from X capacitive touch pad then increase maximum brightness. read 1 seconds for input
  //if input is read from X capacitive touch pad then decrease maximum brightness. read 1 seconds for input.
  //if input is not recieved then assume this is the brightness the user wants.
  //else do nothing.
}

void button() {
  if (CircuitPlayground.leftButton())
  {
    //if left button is pressed then turn ON or OFF the LED
    activate();
  }
  //if user presses right button right after.
  if (CircuitPlayground.rightButton())
  {
    //if right button is pressed then set a new color for the LEDs.
    setCustom();
  }
}

void modusOperandi() {
  if (CircuitPlayground.slideSwitch() == true) {
    CircuitPlayground.clearPixels(); //turn off all LEDs to begin fireplace mode
    fireplace();
  }
  else {
    //set some flags to say standard. 
  }

}

void fireplace() {
  CircuitPlayground.setBrightness(brightness);
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(25));
  }
}

void adjustB() {
  brightness = CircuitPlayground.lightSensor();
  Serial.print("Sensor:"); Serial.print(brightness); Serial.print(",");
  //map the sensor value to a range the LED can accept.
  brightness = map(brightness, 0, 1023, 0, maxBright);
  //invert the brightness because sensor and pixel should be inversly related
  brightness = map(brightness, 0, maxBright, maxBright, 0);
  Serial.print("Pixel:"); Serial.println(brightness);

  allLEDs();
}

void allLEDs() {
  //set the onboard LEDs to the pixel brightness
  CircuitPlayground.setBrightness(brightness);
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, red, green, blue);
  }
}
