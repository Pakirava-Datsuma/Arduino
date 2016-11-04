#include <Wire.h>
#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

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
#define  LCD_CHARS_TOTAL LCD_CHARS_IN_LINE * LCD_LINES

//  Encoder with press_btn
#define PIN_ENCODER_CLK 3
#define PIN_ENCODER_DT 2
#define PIN_ENCODER_SW 10


//          Software CONSTs

#define LED_TIME_ON 1
#define LED_TIME_STEP 20
#define LED_DIST_MODIFIER 3

#define DIST_CHANGE_LIMIT 2

#define  VOLUME_MIN  1
#define  VOLUME_MAX  LCD_CHARS_IN_LINE

#define  SHOW_STARTUP_CONFIG_DELAY 3000

Ultrasonic ultrasonic(PIN_ULTRASONIC_TRIG, PIN_ULTRASONIC_ECHO);
LiquidCrystal_I2C lcd(LCD_ADDR,LCD_CHARS_IN_LINE,LCD_LINES);
Encoder myEnc( PIN_ENCODER_DT, PIN_ENCODER_CLK );

int stepCounter;
int ledStatusCounter;
int distance, oldDistance;
int oldDistChange;
int volume = VOLUME_MAX/2, oldVolume = VOLUME_MIN;
int ledTimeOff = 1;
long rotation, oldRotation;
int encButtonState, oldEncButtonState;
char configStr[LCD_CHARS_TOTAL];

void setup() { 
  Serial.begin (9600); 
  pinMode(OUT_PIN_LED, OUTPUT);

  //LCD 1602
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  
  sprintf(configStr, "sonar: TRIG,ECHO > %d, %d"
    , PIN_ULTRASONIC_TRIG
    , PIN_ULTRASONIC_ECHO);
  showStartConfig (configStr);
  
  sprintf(configStr, "encoder: DT,CLK > %d, %d"
    , PIN_ENCODER_DT
    , PIN_ENCODER_CLK);
  showStartConfig (configStr);
  
  lcd.clear();
} 

void loop() { 
  int ledStatus;
  String volumeStr;
  
  oldDistance = distance;
  distance = ultrasonic.Ranging(false); //distance = 0;//
  int distChangeSpeed = distance;
  int distChange = distance - oldDistance;

  oldRotation = rotation;
  rotation = myEnc.read()/4;
  oldEncButtonState = encButtonState;
  encButtonState = digitalRead(PIN_ENCODER_SW);
  
  distChange = ( (distChange/oldDistChange) > DIST_CHANGE_LIMIT
      ? oldDistChange 
      : distChange);
  oldDistChange = distChange;
  oldVolume = volume;
  volume += distChange;
  volume = min(max(volume, VOLUME_MIN), VOLUME_MAX);
  
  if ((volume != oldVolume)
      ||  (rotation != oldRotation)
      ||  ((oldEncButtonState != encButtonState)
           &&  (encButtonState == LOW))) {

    for (int i = 0; i < volume; i++) 
      volumeStr += '+';
    for (int i = volume; i<VOLUME_MAX; i++)
      volumeStr += ' ';
    //if (volume != oldVolume) {
      Serial.print (rotation);
      Serial.print ("  ");
      Serial.print(ledTimeOff);
      Serial.println(volumeStr);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(rotation);
      lcd.setCursor(LCD_CHARS_IN_LINE-5, 0);
      lcd.print(encButtonState);
      lcd.setCursor(0, 1);
      lcd.print(volumeStr);

      ledTimeOff = VOLUME_MAX-volume+1;
    //}
  }
  if (ledStatusCounter < ledTimeOff) {
    if (ledStatusCounter==0) digitalWrite(OUT_PIN_LED, LOW);
    ledStatusCounter++;
  } 
  else {
    digitalWrite(OUT_PIN_LED, HIGH);
    ledStatusCounter=0;
  }
/*    Serial.print(" step ");
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

void showStartConfig (String string) {
  lcd.clear();
  for (int line = 0; line < LCD_LINES; line++) {
    lcd.setCursor(0, line);
    lcd.print(string.substring((LCD_CHARS_IN_LINE * line),(LCD_CHARS_IN_LINE * (line+1) - 1)));
  }
  delay(SHOW_STARTUP_CONFIG_DELAY);
}

