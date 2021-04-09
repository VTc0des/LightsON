#include <Adafruit_CircuitPlayground.h>

int value;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels(); 
}

void loop() {
  value = CircuitPlayground.lightSensor();
  Serial.print("Sensor:");
  Serial.print(value);
  Serial.print(",");
  //turn to range and invert
  value = map(value, 1, 1023, 0, 255);
  value = map(value, 0, 255, 255, 0);
  Serial.print("Pixel:");
  Serial.println(value);

  //turn on LEDs
  //set brightness
  CircuitPlayground.setBrightness(value);
  for (int i = 0; i < 10; i++) {
  }
    CircuitPlayground.setPixelColor(i, 0xFF0000);
}
