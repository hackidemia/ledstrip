#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<2> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 60 * 5
rgb_color colors[LED_COUNT];

// The color values
rgb_color color;
rgb_color black;

// LED index
int index = 0;

// LED index adder
int adder = 1;

void setup()
{
  // Start up the serial port, for communication with the PC
  Serial.begin(115200);
  Serial.println("Ready to read colors :)");

  // Gain calibration
  for (int pin = 3; pin <= 8; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  // Turn on the sesnor LED
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  // Define black color
  black.red = 0;
  black. green = 0;
  black.blue = 0;
}

void loop()
{
  // Read the color from the sensor
  //int red = ((analogRead(A0) * 100)  / 16);
  //int green = ((analogRead(A1) * 130 ) / 22);
  //int blue = ((analogRead(A2) * 200 ) / 22);
  int red = analogRead(A0) * 10;
  int green = analogRead(A1) * 14;
  int blue = analogRead(A2) * 17;
  //color.red = 0;
  //color.green = 0;
  //color.blue = 0;

  // Check if the sensor sees a bright red, green or blue
  if (red > 600) {
    if (color.red != 255) color.red++;
    if (color.green != 0) color.green--;
    if (color.blue != 0) color.blue--;
  } else if (green > 600) {
    if (color.red != 0) color.red--;
    if (color.green != 255) color.green++;
    if (color.blue != 0) color.blue--;
  } else if (blue > 600) {
    if (color.red != 0) color.red--;
    if (color.green != 0) color.green--;
    if (color.blue != 255) color.blue++;
  }

  // Update the colors buffer.
  if (index == LED_COUNT) adder = -1;
  else if (index == 0) adder = 1;
  colors[index] = black;
  index += adder;
  colors[index] = color;

  // Write to the LED strip
  ledStrip.write(colors, LED_COUNT);

  // Debug
  Serial.print("red: ");
  Serial.print(red);
  Serial.print(" green: ");
  Serial.print(green);
  Serial.print(" blue: ");
  Serial.println(blue);

  delay(5);
}
