#include <Wire.h>
#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h>

//          Harware CONSTs

  // onboard LED
#define OUT_PIN_LED 13

  // HC-SR04 Ultrasonic distance measurer
#define  PIN_ULTRASONIC_TRIG  8
#define  PIN_ULTRASONIC_ECHO  9

  //  LCD1602_I2C Liquid crystal screen 
  //    2 lines x 16 characters with I2C
  //  LCD_I2C have to be connected
  //    SCL > A5
  //    SDA > A4
#define  LCD_ADDR  63
#define  LCD_LINES  2
#define  LCD_CHARS_IN_LINE  16

//          Software CONSTs

#define LED_TIME_ON 1
#define LED_TIME_STEP 20
#define LED_DIST_MODIFIER 3

#define DIST_CHANGE_LIMIT 2

#define  VOLUME_MIN  1
#define  VOLUME_MAX  LCD_CHARS_IN_LINE


Ultrasonic ultrasonic(PIN_ULTRASONIC_TRIG, PIN_ULTRASONIC_ECHO);
LiquidCrystal_I2C lcd(LCD_ADDR,LCD_CHARS_IN_LINE,LCD_LINES);

int stepCounter;
int ledStatusCounter;
int distance, oldDistance;
int oldDistChange;
int volume, oldVolume;
int ledTimeOff = 1;

void setup() { 
  Serial.begin (9600); 
  pinMode(OUT_PIN_LED, OUTPUT);

  //LCD 1602
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("iarduino.ru");
  lcd.setCursor(8, 1);
  lcd.print("LCD 1602");
} 

void loop() { 
  int ledStatus;
  String volumeStr;
  oldDistance = distance;
  distance = ultrasonic.Ranging(false);
  //int distChangeSpeed = distance;
  int distChange = distance - oldDistance;
  if ((abs(distChange) < DIST_CHANGE_LIMIT)
    && (oldDistChange != -distChange)) {

    distChange = ( (distChange/oldDistChange) > DIST_CHANGE_LIMIT
      ? oldDistChange 
      : distChange);
    oldDistChange = distChange;
    oldVolume = volume;
    volume += distChange;
    volume = min(max(volume, VOLUME_MIN), VOLUME_MAX);
    for (int i = 0; i < volume; i++) 
      volumeStr += '+';
    for (int i = volume; i<VOLUME_MAX; i++)
      volumeStr += ' ';
    if (volume != oldVolume) {
      Serial.print(ledTimeOff);
      Serial.println(volumeStr);
      lcd.setCursor(0, 1);
      lcd.print(volumeStr);
      
      ledTimeOff = VOLUME_MAX-volume+1;
    }
  }
  if (ledStatusCounter < ledTimeOff) {
    if (ledStatusCounter==0) digitalWrite(OUT_PIN_LED, LOW);
    ledStatusCounter++;
  } 
  else {
    digitalWrite(OUT_PIN_LED, HIGH);
    ledStatusCounter=0;
  }
/*
    Serial.print(" step ");
    Serial.print(stepCounter);
    Serial.print(" distance ");
    Serial.print(distance);
    Serial.print(" ledStatusCounter ");
    Serial.print(ledStatusCounter);
    Serial.print(" ledTimeOff ");
    Serial.print(ledTimeOff);
*/
  delay(LED_TIME_STEP);
}





