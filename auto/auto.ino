#include <U8x8lib.h>
#include <U8g2lib.h>
#include <Servo.h> 
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 
Servo servo1;
Servo servo2;
const int buttonPin1 = 4;
const int buttonPin2 = 5;
const int buttonPin3 = 6;
int matka = 0;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int tormays = 0;

void setup() 
{ 
  servo1.attach(9);
  servo2.attach(10);
  servo1.write(90);
  servo2.write(90);
  Serial.begin(9600);
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
} 

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);

  if (buttonState2 == HIGH) {
    suoraan();
    tormays = 0;
    
  }
  else if (buttonState1 == HIGH) {
    kaanny_vasen();
    tormays += 1;
  } else if (buttonState3 == HIGH) {
    kaanny_oikea();
    tormays += 1;
  }
  u8x8.setCursor(0,0);
  u8x8.print(tormays);
  buttonState1 = 0;
  buttonState2 = 0;
  buttonState3 = 0;
}
void kaanny_vasen() {
  servo1.write(0);
  servo2.write(180);
  delay(1000);
  suoraan();
}
void kaanny_oikea() {
  servo2.write(0);
  servo1.write(180);
  delay(1000);
  suoraan();
}
void suoraan() {
  servo1.write(180);
  servo2.write(180);
}
void reset() {
  servo1.write(90);
  servo2.write(90);
}
//u8x8.setCursor(0,0);
//u8x8.print(matka);
