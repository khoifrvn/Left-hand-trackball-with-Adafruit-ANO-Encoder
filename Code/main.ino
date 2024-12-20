#include "Adafruit_seesaw.h"
#include <pimoroniTrackball.h>
#include "Wire.h"
#include<TinyUSB_Mouse_and_Keyboard.h>

#define SS_SWITCH_SELECT 1
#define SS_SWITCH_UP     2
#define SS_SWITCH_LEFT   3
#define SS_SWITCH_DOWN   4
#define SS_SWITCH_RIGHT  5

#define SEESAW_ADDR      0x49

Adafruit_seesaw ss = Adafruit_seesaw(&Wire1);
extern pimoroniTrackball trackball;
int32_t encoder_position;

int x_move = 0, y_move = 0;
int sensivity;

int move_mode = 1;
static bool isClicking = false;
static unsigned long clickStartTime = 0;

int left_val = 0;
int right_val = 0;
int up_val = 0;
int down_val = 0;
int click_val = 0;
int release_val = 0;

int encoder_mode = 1;
static bool isPressing = false;
static unsigned long pressStartTime = 0;

int sleep_flg = 0;
static unsigned long sleepStartTime = 0;
int lightoff = false;
int brighness = 150;

void setup() {
  Mouse.begin();
  Keyboard.begin();

  Serial.begin(115200);
  //while (!Serial) delay(10);

  // Initialize I2C
  Serial.println("Initializing I2C...");
  Wire1.begin();

  // Initialize Seesaw Encoder
  Serial.println("Looking for seesaw encoder...");
  if (!ss.begin(SEESAW_ADDR)) {
    Serial.println("Seesaw encoder not found!");
    while (1) delay(10);
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
  trackball.begin(0xA, Wire1); 
  if (trackball.isConnected()) {
    Serial.println("Trackball connected.");
    for (int i = 20; i<= 255; i++){
      trackball.setRed(i); delay(12); 
    }
    for (int i = 20; i<= 255; i++){
      trackball.setBlue(i); delay(12); 
    }
    for (int i = 20; i<= 255; i++){
      trackball.setGreen(i); delay(12); 
    }
    for (int i = 20; i<= 255; i++){
      trackball.setWhite(i); delay(12); 
    }
    trackball.setRGBW(0, 0, 0, 0);
    for (int i = 255; i>= 10; i--){
      trackball.setRGBW(i, i, i, i); delay(10); 
    }
    trackball.setRGBW(0, 0, 0, 0);
    for (int i = 20; i<= 255; i++){
      if (i % 2){trackball.setBlue(i); delay(22);}
      else trackball.setRGBW(0, 0, 0, 0); delay(22); 
    }
    for (int i = 255; i >= 150; i--){
      if (i % 2 != 0){trackball.setBlue(i); delay(15);}
      else trackball.setRGBW(0, 0, 0, 0); delay(15);  
    }
  } else {
    Serial.println("Trackball not connected!");
    while (1) delay(1000);
  }
}

void loop() {
// Seesaw button check
  if (!ss.digitalRead(SS_SWITCH_UP)) {
    sleep_flg = false;
    Keyboard.press(KEY_UP_ARROW);
    Serial.println("UP pressed!"); 
    delay(10);
    Keyboard.release(KEY_UP_ARROW);
    int t = 150;                          
    delay(t);
    while(!ss.digitalRead(SS_SWITCH_UP)){
      t -=10;
      t = (t<=0)? 1: t;
      Keyboard.press(KEY_UP_ARROW);
      delay(t);
      Keyboard.release(KEY_UP_ARROW);
    }
  } 

  if (!ss.digitalRead(SS_SWITCH_DOWN)) {
    sleep_flg = false;
    Keyboard.press(KEY_DOWN_ARROW);
    Serial.println("DOWN pressed!");
    delay(10); 
    Keyboard.release(KEY_DOWN_ARROW);
    int t = 150;                          
    delay(t);
    while(!ss.digitalRead(SS_SWITCH_DOWN)){
      t -=10;
      t = (t<=0)? 1: t;
      Keyboard.press(KEY_DOWN_ARROW);
      delay(t);
      Keyboard.release(KEY_DOWN_ARROW);
    }
  } 

  if (!ss.digitalRead(SS_SWITCH_SELECT)) {
    sleep_flg = false;
    Serial.println("SELECT pressed!");
    delay(200);

    if(ss.digitalRead(SS_SWITCH_SELECT))Mouse.click(MOUSE_LEFT);

    if (!isPressing & !ss.digitalRead(SS_SWITCH_SELECT)) { 
      isPressing = true; 
      pressStartTime = millis(); 
      Serial.println("Pressed. Start timing.");
    }
  }
  
  if (!ss.digitalRead(SS_SWITCH_LEFT)) {
    sleep_flg = false;
    Keyboard.press(KEY_LEFT_ARROW);
    Serial.println("LEFT pressed!");
    delay(10); 
    Keyboard.release(KEY_LEFT_ARROW);
    int t = 150;                          
    delay(t);
    while(!ss.digitalRead(SS_SWITCH_LEFT)){
      t -= 8;
      t = (t<=0)? 1: t;
      Keyboard.press(KEY_LEFT_ARROW);
      delay(t);
      Keyboard.release(KEY_LEFT_ARROW);
    }
  }

  if (!ss.digitalRead(SS_SWITCH_RIGHT)) {
    sleep_flg = false;
    Keyboard.press(KEY_RIGHT_ARROW);
    Serial.println("RIGHT pressed!");
    delay(10); 
    Keyboard.release(KEY_RIGHT_ARROW);
    int t = 150;                          
    delay(t);
    while(!ss.digitalRead(SS_SWITCH_RIGHT)){
      t -=10;
      t = (t<=0)? 1: t;
      Keyboard.press(KEY_RIGHT_ARROW);
      delay(t);
      Keyboard.release(KEY_RIGHT_ARROW);
    }
  }

//Encoder process
  int32_t new_position = ss.getEncoderPosition();
  if (encoder_position != new_position) {
    sleep_flg = false;
    Serial.print("Encoder Position: ");
    Serial.println(new_position);
    
    switch (encoder_mode){
      case 1:
        Mouse.move(0, 0, -(new_position - encoder_position));
        break;
      case 2:
        Keyboard.press(KEY_LEFT_SHIFT);
        Mouse.move(0, 0, -(new_position - encoder_position)); 
        Keyboard.release(KEY_LEFT_SHIFT);
        break;
    }
    encoder_position = new_position;
  }

// Trackball check for movement
  if (trackball.changed()) {
    sleep_flg = false;
    
    click_val = trackball.click();
    release_val = trackball.release();

    if (click_val != 0){
      Serial.println("Mouse click");
      Mouse.click(MOUSE_LEFT);

      if (!isClicking) { 
        isClicking = true; 
        clickStartTime = millis(); 
        Serial.println("Trackball clicked. Start timing.");
      }
    }

    if (release_val != 0){
      Serial.println("Mouse release");
      Mouse.release();
      delay(200);

      isClicking = false;
      clickStartTime = 0;
    }

    x_move = y_move = 0;
    left_val = trackball.left();
    right_val = trackball.right();
    up_val = trackball.up();
    down_val = trackball.down();

    if (left_val > 0) {
      y_move += left_val;
      Serial.print("Left: "); Serial.println(left_val);
    }
    if (right_val > 0) {
      y_move -= right_val;
      Serial.print("Right: "); Serial.println(right_val);
    }
    if (up_val > 0) {
      x_move -= up_val;
      Serial.print("Up: "); Serial.println(up_val);
    }
    if (down_val > 0) {
      x_move += down_val;
      Serial.print("Down: "); Serial.println(down_val);
    }

    if (x_move != 0 || y_move != 0) {
      if (move_mode == 1) {
        sensivity = (abs(x_move) > 6 || abs(y_move) > 6) ? 5 : 15;

        int magRange = 3;
        int outRange = 127;
        int inRange = magRange * sensivity;

        int xMove = map(x_move, -inRange, inRange, -outRange, outRange);
        int yMove = map(y_move, -inRange, inRange, -outRange, outRange);
        xMove = (xMove > 100) ? 100 : xMove;
        yMove = (yMove > 100) ? 100 : yMove;
        xMove = (xMove < -100) ? -100 : xMove;
        yMove = (yMove < -100) ? -100 : yMove;
        
        Mouse.move(xMove, yMove, 0);
        Serial.print("Moved Mouse X: "); Serial.print(xMove);
        Serial.print(" Y: "); Serial.println(yMove);

      }
      else if (move_mode == 2){
        int scrollSpeed = 1; // Adjust scroll speed as desired
        int hScroll = (x_move > 0) ? -scrollSpeed : (x_move < 0) ? scrollSpeed : 0;
        int vScroll = (y_move > 0) ? -scrollSpeed : (y_move < 0) ? scrollSpeed : 0;

        if (vScroll != 0) {
          Mouse.move(0, 0, vScroll); 
          Serial.print(" Vertically: "); Serial.println(vScroll);
        }
        if (hScroll != 0) {
          Keyboard.press(KEY_LEFT_SHIFT);
          Mouse.move(0, 0, hScroll); 
          Keyboard.release(KEY_LEFT_SHIFT);
          Serial.print("Scrolled Horizontally: "); Serial.print(hScroll);
        }
      }
    }
  }

//trackball switch mode process
  if (isClicking) {
    sleep_flg = false;
    unsigned long currentDuration = millis() - clickStartTime;
    Serial.print("Duration clicked: ");
    Serial.println(currentDuration);
    
    if (currentDuration >= 1000) {
      move_mode = (move_mode == 1) ? 2 : 1; 
      Serial.print("Mode switched to: ");
      Serial.println(move_mode);
      isClicking = false;
    }
  }

//encoder switch mode process
  if (ss.digitalRead(SS_SWITCH_SELECT)){
    isPressing = false;
  }
  if (isPressing & !ss.digitalRead(SS_SWITCH_SELECT)) {
    sleep_flg = false;
    unsigned long currentDuration1 = millis() - pressStartTime;
    Serial.print("Duration Press: ");
    Serial.println(currentDuration1);
    
    if (currentDuration1 >= 600) {
      encoder_mode = (encoder_mode == 1) ? 2 : 1; 
      Serial.print("Encoder Mode switched to: ");
      Serial.println(encoder_mode);
      isPressing = false;
      if (encoder_mode == 1) {
        trackball.setRGBW(0, 0, 0, 0);
        trackball.setGreen(150);
      } else {
        trackball.setRGBW(0, 0, 0, 0);
        trackball.setWhite(150);
      }
      delay(500);
    }
  }

//sleep mode process
  if (!sleep_flg){
    sleepStartTime = millis();
    sleep_flg = true;
    lightoff = false;
    brighness = 150;

    if (move_mode == 1) {
      trackball.setRGBW(0, 0, 0, 0);
      trackball.setBlue(brighness);
    } else {
      trackball.setRGBW(0, 0, 0, 0);
      trackball.setRed(brighness);
    }
  }
  else{
    unsigned long sleepTimer = millis() - sleepStartTime;

    if(sleepTimer >= 300000 & !lightoff){
      trackball.setRGBW(0, 0, 0, 0);
      Serial.println("Light off");
      lightoff = true;
    }
  }
}
