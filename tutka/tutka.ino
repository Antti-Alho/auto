#include <Time.h>
#include <TimeLib.h>
#include <U8x8lib.h>
#include <U8g2lib.h>
#include <Servo.h> 
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 
Servo servo1;
Servo servo2;
Servo echo;
const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int buttonPin5 = 5;
const int buttonPin6 = 6;
const int buttonPin7 = 7;
const int buttonPin8 = 8;
const int trigPin = 13;
const int echoPin = 12;
const int metri = 3250;
const int turnTime = 290;

float area = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;
int buttonState7 = 0;
int buttonState8 = 0;
int button8Memory = 0;
int programState = 0;
int tormays = 0;

uint8_t tiles[10][8] =  {
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00},
  {0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00},
  {0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
  {0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00},
  {0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00},
  {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00},
  {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
  {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
};
long duration = 0;
int distance = 0;

void setup() { 
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  servo1.attach(9);
  servo2.attach(10);
  echo.attach(11);
  
  Serial.begin(9600);
  
  servo1.write(90);
  servo2.write(90);
  echo.write(90);
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  setTime(0);
} 

void loop() {
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  buttonState7 = digitalRead(buttonPin7);
  buttonState8 = digitalRead(buttonPin8);

  //choose what to do
  if (buttonState2 == LOW) {
    u8x8.setCursor(0,2);
    u8x8.print("progstate = 1");
    programState = 1;
  } else if (buttonState3 == LOW) {
    u8x8.setCursor(0,2);
    u8x8.print("progstate = 2");
    programState = 2;
  } else if (buttonState4 == LOW) {
    u8x8.setCursor(0,2);
    u8x8.print("progstate = 3");
    programState = 3;      
  }
  
  // start chosen program 
  if (buttonState8 == LOW) {
    aika = millis();
    if (button8Memory == 1) {
      button8Memory = 0;
      u8x8.setCursor(0,1);
      u8x8.print("mem8 = 0");
      delay(500);
    } else {
      button8Memory = 1;
      u8x8.setCursor(0,1);
      u8x8.print("mem8 = 1");
      delay(500);
    }
  }
  if (button8Memory == 1) {   
    if (programState == 1) {
      startCorner();
    } else if (programState == 2) {
      reset();
    } else if (programState == 3) {
      drawPic();
    } 
  }
}

void kaanny_oikea() {
  servo1.write(0);
  servo2.write(180);
  delay(290);
}
void kaanny_vasen() {
  servo2.write(0);
  servo1.write(180);
  delay(290);
}
void suoraan() {
  servo1.write(180);
  servo2.write(180);
}
void reset() {
  servo1.write(90);
  servo2.write(90);
}

void startCorner(){
  int collisiontime1 = 0;
  int collisiontime2 = 0;
  setTime(0);
  suoraan();
  while (programState == 1) {
    
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
    buttonState4 = digitalRead(buttonPin4);
    buttonState5 = digitalRead(buttonPin5);
    buttonState6 = digitalRead(buttonPin6);
    buttonState7 = digitalRead(buttonPin7);
    buttonState8 = digitalRead(buttonPin8);

    if (buttonState7 == LOW || buttonState6 == LOW || buttonState5 == LOW) {
      kaanny_oikea();
      suoraan();
      tormays += 1;
      if (tormays == 1){
        collisiontime1 = millis();
        setTime(0);
      } else if (tormays == 2) {
        collisiontime2 = millis();
      }
    }
    if (buttonState2 == LOW || buttonState3 == LOW || buttonState4 == LOW) {
      kaanny_vasen();
      suoraan();
      tormays += 1;
      if (tormays == 1){
        collisiontime1 = millis();
        setTime(0);
      } else if (tormays == 2) {
        collisiontime2 = millis();
      }
    }
    
    if (tormays == 2) {
      button8Memory = 0;
      reset();
      area = (float)((float)collisiontime1/metri)*((float)collisiontime2/metri);
      u8x8.setCursor(0,0);
      u8x8.print(area);
      programState = 0;
    }
  }
}

void drawPic(){
  int dist1 = 0;
  int dist2 = 0;
  suoraan();
  u8x8.setCursor(0,1);
  u8x8.print("                ");
  u8x8.setCursor(0,2);
  u8x8.print("                ");
  while(programState == 3){
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
    buttonState4 = digitalRead(buttonPin4);
    buttonState5 = digitalRead(buttonPin5);
    buttonState6 = digitalRead(buttonPin6);
    buttonState7 = digitalRead(buttonPin7);
    buttonState8 = digitalRead(buttonPin8);
    draw(calcdistance());
    if (buttonState7 == LOW || buttonState6 == LOW || buttonState5 == LOW) {
      kaanny_oikea();
      suoraan();
    }
    if (buttonState2 == LOW || buttonState3 == LOW || buttonState4 == LOW) {
      kaanny_vasen();
      suoraan();
    }
    if (calcdistance() < 20) {
      reset();
      echo.write(0);
      delay(300);
      dist1 = calcdistance();
      echo.write(180);
      delay(300);
      dist2 = calcdistance();
      echo.write(90);
      delay(300);
      if (dist1 >= dist2) {
        kaanny_oikea();
        suoraan();
      } else {
        kaanny_vasen();
        suoraan();
      }
    } else {
      suoraan();
    }
  }
}

void draw(int a) {
  int b = a/10;
  int c = a%10;
  int x = 0;
  u8x8.setCursor(0,1);
  u8x8.print(b);
  u8x8.setCursor(0,2);
  u8x8.print(c);
  u8x8.setCursor(0,0);
  u8x8.print("                ");
  for (x; x<b; x++ ){
    u8x8.drawTile(x, 0, 1, tiles[8]);
  }
  u8x8.drawTile(b, 0, 1, tiles[c]);
}

int calcdistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = duration*0.034/2;
  u8x8.setCursor(0,3);
  u8x8.print("dist:");
  u8x8.print(distance);
  return distance;
}
