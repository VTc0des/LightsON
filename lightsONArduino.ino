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
//button debounce and state variables
int leftButton;
int leftButtonState;
int lastLeft = LOW;

int rightButton;
int rightButtonState;
int lastRight = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long buttonTime = 60;

/*COLOR SENSOR*/
//DEFAULT VALUE IS WHITE
uint8_t red;
uint8_t green;
uint8_t blue;

/*LIGHT PWM*/
int brightness;
int maxBright = 255;

/*FUNCTION DECLARATIONS*/
void activate();      //function to turn on or off the device
void setCustom();     //function to set a custom color for the lights
void adjustMaxB();    //function for user to tap capacitive touch pads to set maximum brightness.
void button();        //function to turn ON or OFF all circuit playground
int debounceLeft();  //function to debounce the button input
int debounceRight();  //function to debounce the button input
void modusOperandi(); //function to toggle mode from standard to fireplace
void fireplace();     //function to randomly flash red, orange, and yellow LED colors in a random fashion.
void adjustB();       //function to adjust the brightness of the LED based on room light
void setDefault();  //function with default values of red, green, and blue pixels.
void allLEDs();       //function to turn on all the LEDs.

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();

  //set random value for fireplace flickering
  randomSeed(CircuitPlayground.lightSensor());
  
  //turn ON the LEDs the moment the circuit is connected to power.
  //set default to white
  setDefault();
  isON = false;
  isOFF = true;
  activate();

  /*AccelTap Section - DOES NOT WORK
    //establish tap interrupt
    CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
    //detect both single and double taps
    CircuitPlayground.setAccelTap(2, TAP_THRESHOLD);
    attachInterrupt(digitalPinToInterrupt(CPLAY_LIS3DH_INTERRUPT), activate, FALLING);
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
    Serial.println("activate");
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
  CircuitPlayground.senseColor(red, green, blue);

  // Gamma correction makes LED brightness appear more linear
  red = CircuitPlayground.gamma8(red);
  green = CircuitPlayground.gamma8(green);
  blue = CircuitPlayground.gamma8(blue);

  if (red == 0 && green == 0 && blue == 0) {
    setDefault();
  }
  Serial.print(red); Serial.print(","); Serial.print(green); Serial.print(","); Serial.println(blue);
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
  //debounce button input
  leftButton = debounceLeft();
  if (leftButton)
  {
    //if left button is pressed then turn ON or OFF the LED
    activate();
  }

  //if slide switch is in standard mode, read the custom color button
  if (CircuitPlayground.slideSwitch() == false) {
    rightButton = debounceRight();
    if (rightButton)
    {
      //if right button is pressed then set a new color for the LEDs.
      setCustom();
    }
  }
}

int debounceLeft() {
  lastDebounceTime = millis();                            //take most recent system time to ensure the while loop begins
  while ((millis() - lastDebounceTime) < buttonTime) {
    int state = CircuitPlayground.leftButton();           //save state to a local variable

    if (state != lastLeft) {                              //update the time if the reading changed.
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {  //if enough time has passed, and the state changed, save the last state
      if (state != leftButtonState) {
        leftButtonState = state;
      }
      break;                                              //break the while loop if this condition is met.
    }
    lastLeft = state;                                     //save the button state to compare to
  }
  return leftButtonState;
}

int debounceRight() {
  lastDebounceTime = millis();                             //take most recent system time to ensure the while loop begins
  while ((millis() - lastDebounceTime) < buttonTime) {
    int state = CircuitPlayground.rightButton();           //save state to a local variable

    if (state != lastRight) {                              //update the time if the reading changed.
      // reset the debouncing timer
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {   //if enough time has passed, and the state changed, save the last state
      if (state != rightButtonState) {
        rightButtonState = state;
      }
      break;                                               //break the while loop if this condition is met.
    }
    lastRight = state;                                     //save the button state to compare to
  }
  return rightButtonState;
}

void modusOperandi() {
  if (CircuitPlayground.slideSwitch() == true) {
    fireplace();
  }
  else {
    //do nothing, you are in standard mode. 
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
  //Serial.print("Sensor:"); Serial.print(brightness); Serial.print(",");
  //map the sensor value to a range the LED can accept.
  brightness = map(brightness, 0, 1023, 0, maxBright);
  //invert the brightness because sensor and pixel should be inversly related
  brightness = map(brightness, 0, maxBright, maxBright, 0);
  //Serial.print("Pixel:"); Serial.println(brightness);

  allLEDs();
}

void setDefault() {
  red = 255;
  green = 255;
  blue = 255;
}

void allLEDs() {
  //set the onboard LEDs to the pixel brightness
  CircuitPlayground.setBrightness(brightness);
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, red, green, blue);
  }
}
