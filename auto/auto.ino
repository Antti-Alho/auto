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
const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int buttonPin5 = 5;
const int buttonPin6 = 6;
const int buttonPin7 = 7;
const int buttonPin8 = 8;
const int metri = 3250;
const int turnTime = 310;

int matka = 0;
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
int aika = 0;
int aika2 = 0;
int aika3 = 0;

void setup() { 
  Serial.begin(9600);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);
  
  servo1.attach(9);
  servo2.attach(10);
  servo1.write(90);
  servo2.write(90);
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
    
  if (buttonState8 == LOW) {
    aika = millis();
    if (button8Memory == 1) {
      button8Memory = 0;
      delay(500);
    } else {
      button8Memory = 1;
      delay(500);
    }
  }
  if (button8Memory == 1) {
    //s
    if (programState == 1) {

    } else if (programState == 2) {

    } else if (programState == 3) {

    } 
  } else {
    programState = 0;
    reset();
  }
  if (buttonState7 == LOW || buttonState6 == LOW || buttonState5 == LOW) {
    kaanny_oikea();
    suoraan();
    tormays += 1;
  }
  if (buttonState2 == LOW || buttonState3 == LOW || buttonState4 == LOW) {
    kaanny_vasen();
    suoraan();
    tormays += 1;
  }
  
  if (tormays == 2) {
    button8Memory = 0;
    reset();    
    aika2 = millis();
    aika3 = (aika2 - aika) - 290;
    matka = aika3 / metri;
    u8x8.setCursor(0,0);
    u8x8.print(matka);    
  }

  if (buttonState7 == LOW || buttonState6 == LOW || buttonState5 == LOW) {
    aika2 = millis();
    aika3 = aika2 - aika;
    u8x8.setCursor(0,0);
    u8x8.print(aika3);
    reset();
    button8Memory = 0;
    delay(500);
    
  }
  if (buttonState2 == LOW || buttonState3 == LOW || buttonState4 == LOW) {
    aika2 = millis();
    aika3 = aika2 - aika;
    u8x8.setCursor(0,0);
    u8x8.print(aika3);
    reset();
    button8Memory = 0;
    delay(500);
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

}

void startMiddle(){

}

void drawPic(){

}

void start(){

}