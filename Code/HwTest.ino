#include "Adafruit_seesaw.h"
#include <pimoroniTrackball.h>
#include "Wire.h"

#define SS_SWITCH_SELECT 1
#define SS_SWITCH_UP     2
#define SS_SWITCH_LEFT   3
#define SS_SWITCH_DOWN   4
#define SS_SWITCH_RIGHT  5

#define SEESAW_ADDR      0x49

Adafruit_seesaw ss = Adafruit_seesaw(&Wire1);
extern pimoroniTrackball trackball;
int32_t encoder_position;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  // Initialize I2C
  Serial.println("Initializing I2C...");
  Wire1.begin();

  // Initialize Seesaw Encoder
  Serial.println("Looking for seesaw encoder...");
  if (!ss.begin(SEESAW_ADDR)) {
    Serial.println("Seesaw encoder not found!");
    while (1) delay(10);  // Halt if the encoder is not found
  } else {
    Serial.println("Seesaw encoder initialized.");
  }

  // Check firmware version
  uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
  if (version != 5740) {
    Serial.print("Unexpected firmware version: ");
    Serial.println(version);
    while (1) delay(10);
  }
  Serial.println("Found Seesaw Product 5740");

  // Configure Seesaw button pins with pull-ups
  ss.pinMode(SS_SWITCH_UP, INPUT_PULLUP);
  ss.pinMode(SS_SWITCH_DOWN, INPUT_PULLUP);
  ss.pinMode(SS_SWITCH_LEFT, INPUT_PULLUP);
  ss.pinMode(SS_SWITCH_RIGHT, INPUT_PULLUP);
  ss.pinMode(SS_SWITCH_SELECT, INPUT_PULLUP);

  // Get starting position of the encoder
  encoder_position = ss.getEncoderPosition();
  ss.enableEncoderInterrupt();

  // Initialize Trackball
  Serial.println("Initializing trackball...");
  trackball.begin(0xA, Wire1);  // Initialize the trackball on I2C address 0xA
  if (trackball.isConnected()) {
    Serial.println("Trackball connected. Testing LEDs...");
    // Test Trackball LEDs
    trackball.setRed(255); delay(500); trackball.setRed(0);
    trackball.setGreen(255); delay(500); trackball.setGreen(0);
    trackball.setBlue(255); delay(500); trackball.setBlue(0);
    trackball.setWhite(255); delay(500); trackball.setWhite(0);
    trackball.setRGBW(255, 255, 255, 255); delay(500);
    trackball.setRGBW(0, 0, 0, 0);
  } else {
    Serial.println("Trackball not connected!");
    while (1) delay(1000);
  }
}

void loop() {
  // Seesaw button check
  if (!ss.digitalRead(SS_SWITCH_UP)) Serial.println("UP pressed!");
  if (!ss.digitalRead(SS_SWITCH_DOWN)) Serial.println("DOWN pressed!");
  if (!ss.digitalRead(SS_SWITCH_SELECT)) Serial.println("SELECT pressed!");
  if (!ss.digitalRead(SS_SWITCH_LEFT)) Serial.println("LEFT pressed!");
  if (!ss.digitalRead(SS_SWITCH_RIGHT)) Serial.println("RIGHT pressed!");

  int32_t new_position = ss.getEncoderPosition();
  if (encoder_position != new_position) {
    Serial.print("Encoder Position: ");
    Serial.println(new_position);
    encoder_position = new_position;
  }

  // Trackball check for movement
  if (trackball.changed()) {
    Serial.print("Left: "); Serial.print(trackball.left());
    Serial.print(" Right: "); Serial.print(trackball.right());
    Serial.print(" Up: "); Serial.print(trackball.up());
    Serial.print(" Down: "); Serial.print(trackball.down());
    Serial.print(" Click: "); Serial.print(trackball.click());
    Serial.print(" Release: "); Serial.println(trackball.release());
  }

  delay(10);
}
