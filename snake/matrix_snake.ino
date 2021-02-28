#include <LedControl.h>

// matrix
int DIN = 12;
int CS = 10;
int CLK = 11;

// joystick
int VRx = A0;
int VRy = A1;
int SW = 2;

// ---
int xPosition = 0;
int yPosition = 0;
int SW_state = 1;
int mapX = 0;
int mapY = 0;

// GAMEPLAY

int speed = 300;

bool direction_ = true;
bool x_y = true; 
int length_ = 1;

int xArray[64];
int yArray[64];

int random_x = 5;
int random_y = 4;

int Cat[8] ={B10001000,B11111000,B10101000,B01110001,B00100001,B01111001,B01111101,B10111110 };


LedControl lc=LedControl(DIN, CLK, CS,0);

void setup() {
  Serial.begin(9600); 
  

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  
  
  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);
//  randomSeed(4);
  
  
}

  
void loop(){



   lc.clearDisplay(0);

  SW_state = digitalRead(SW);

  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);

  mapY = map(xPosition, 0, 1023, 0, 998);
  mapX = map(yPosition, 0, 1023, 0, 998);
  
 
  
Serial.print(random_y);
 lc.setLed(0, random_x, random_y, true);
  if (xArray[0] == random_x && yArray[0] == random_y) {
      length_ += 1;
      lc.clearDisplay(0);
      random_x = random(0, 7);
      random_y = random(0, 7);
  }
    

  for (int i = length_ - 1; i > 0; i--) {
    xArray[i] = xArray[i-1];
    yArray[i] = yArray[i-1];
  }

  way(); // ??? move upward

  
  for (int i = 0; i < length_; i++) {
    lc.setLed(0, xArray[i], yArray[i], true);
  }
 
//  for (int i = 0; i < length_; i++) {
//    lc.setLed(0, xArray[i], yArray[i], true);
//  }

 for (int i = 1; i < length_; i++) {
    if (xArray[0] == xArray[i] && yArray[0] == yArray[i]){
      while (SW_state != 0){
        for(int i=0;i<8;i++) 
          lc.setRow(0,i,Cat[i]);
           SW_state = digitalRead(SW);

            delay(100);
            length_ = 1;
            xArray[0] = 0;
            yArray[0] = 0;
            
      }}
  }
  Serial.println();
//yArray[0]
  delay(speed);
  lc.clearDisplay(0);

  
  
}




void way(){
  if (mapX > 665 && x_y != true){
    direction_ = true;
    x_y = true; 
  } else if (mapX < 332 && x_y != true) {
    direction_ = false;
    x_y = true; 
  } else if (mapY > 665 && x_y != false) {
    direction_ = true;
    x_y = false; 
  } else if (mapY < 332 && x_y != false) {
    direction_ = false;
    x_y = false; 
  } 

if (direction_ == true && x_y == true) {
    if (xArray[0] == 7) {
      xArray[0] = 0;
    } else {
    xArray[0] += 1;
    }
  }

if (direction_ == false && x_y == true) {
    if (xArray[0] == 0) {
      xArray[0] = 7;
    } else {
    xArray[0] -= 1;
    }
  }

if (direction_ == true && x_y == false) {
    if (yArray[0] == 7) {
      yArray[0] = 0;
    } else {
    yArray[0] += 1;
    }
  }

if (direction_ == false && x_y == false) {
    if (yArray[0] == 0) {
      yArray[0] = 7;
      
    } else {
    yArray[0] -= 1;
    }
  }
}
