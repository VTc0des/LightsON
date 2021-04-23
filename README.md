# LightsON 
## Introduction
Illumination is the name of the game when it comes to ZOOM calls. Look bright while you're being bright with LightsON a portable alternative to standing ring lights that is designed to automatically adjust the illumination on your face with power efficient LEDs to supplement your room’s natural light. As the light in your room waxes and wanes, LightsON will too, thus, ensuring there is an even distribution of light on you at all times. 

LightsON is a Circuit Playground enabled, USB powered, energy efficient device that comes in two modes: standard and fireplace. Standard mode operates with the default white light or custom color illumination while fireplace mode flickers the LEDs with red, yellow or orange lights to mimic a fireplace. Use fireplace mode to lighten the mood during virtual movie or game nights or to spice up boring conference calls. 

**LightsON! Flip a switch to lighten the mood.**

## Author's Notes and Credit
The primary author for all the code responsible for device functionality is **Varsha Thomas**

Credit goes to the following people for specific LightsON functionality:
> 'fireplace' mode: adapted from Brithday_Candles.ino, originally developed by **Tony DiCola**
Color sensor: adapted from color_sense.ino, originally developed by **Limor Fried and Tony DiCola**
Button Debounce: adapted from debounce.ino, most recently modified by **Arturo Guadalupi**

## Important Intructions
The code to operate the LightsON device was written, compiled, and executed using Arduino IDE v. 1.8.13 on a Windows 10 platform.
This code is available in the main branch at the [LightsON GitHub Page](https://github.com/VTc0des/LightsON/blob/main/lightsONArduino.ino) in the file labelled `lightsONArduino.ino`

The following sections provide detail on which inputs on the circuit playground are configured. 

## User Interface
Refer to the [circuit playground documentation](https://learn.adafruit.com/introducing-circuit-playground/guided-tour) for a visual identification of the location of the inputs mentioned below. 

The following inputs on the circuit playground are configured for the LightsON device:
*left is on the side of the ON led located on one side of the USB-C port, right is on the side of the LED marked #13 which is located on the other side of the USB-C port*
1. Left Button: push the button to turn ON/OF the LEDs
2. Right Button: push the button to change the color of the LEDs
3. Slide Switch Minus (-): toggle switch to the right (-) position to set the mode to standard (white or custom color light)
4. Slide Switch Plus (+): toggle switch to the left (+) position to set the mode to fireplace*
5. Capacitive Touch Pad **#2**: tap to **decrease** the maximum brightness of the LEDs by 10, hold to **decrease** the brightness quickly
6. Capacitive Touch Pad **#9**: tap to **increase** the maximum brightness of the LEDs by 10, hold to **increase** the brightness quickly
7. Light Sensor (light dependent resistor): main functionality is to monitor ambient light and increase brightness if the ambient light is low, decrease brightness if ambient light is high. If the right button is pressed, the light sensor doubles as a color sensor to detect the color of object placed flush against it and automatically changes the color of all LEDs until reset or right buttons are pushed. 
8. Sound Sensor: blow on the circuit playground to "extinguish" the fireplace after use. Press the reset button to restore fireplace mode
9. Reset: resets the circuit playground device to restore preset parameters 

> Functionality like ON/OFF, custom color, increasing or decreasing brightness is limited to standard mode and is not currently available in fireplace mode.

## Device Workflow
1. Connect the circuit playground to the USB port on your laptop using a USB to USB-C cable.
2. Upload the code in lightsONArduino.ino to the circuit playground. 
3. If the switch is at the (-) position upon startup, standard mode is activated. If the switch is at the (+) position upon startup, fireplace mode is activated. 
4. Assuming you are in standard mode (slide switch -), press the left button once to turn off the LEDs if it already ON, press the left button again to turn ON the LEDs if it is already OFF. 
5. Press the right button to set custom color for the LEDs. Hold an object of the desired color against the light sensor marked by the 'eye' icon on the left side of the circuit playground. If no object is placed against the sensor, the default color is white. 
6. To adjust the maximum brightness of the LEDs, touch/hold the capacitive pad #2 to decrease the brightness, OR touch/hold pad #9 to increase the brightness.
7. The light sensor will auto detect and adjust brightness up to the maximum brightness set by you as long as the device is connected to power. 
8. The device can be made more portable by using a small battery pack after the code is uploaded to the circuit playground. 
9. Enjoy!
