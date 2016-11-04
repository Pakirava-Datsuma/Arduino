// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 6     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
int led = 13;
//blink mode: positive blinks shows how value grater than normal
// negative blinks shows how value lesser than normal

float humidityPercentsPerBlink = 5/1;
float normalHumidity = 50.0;
float humidityRounding = +1;

boolean inverseBlinks = false;

void setup() {
//  Serial.begin(9600);  
  dht.begin();
  pinMode(led, OUTPUT);

  //show settings
  //percents per blink
  blinkDigit(  humidityPercentsPerBlink );
  pause();
  
/* 
//test digit output on startup
  //Serial.println("test:");
  for (int i = 0; i < 13; i++) {
    pause();
    //Serial.println();
    //Serial.println(i);
    blinkDigit(i);
  }    
*/
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  pause();
  float humidity = dht.readHumidity();
//  Serial.println(humidity);
//  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  //if (! (isnan(t) || isnan(h))) {
  if (! isnan(humidity)) {

    humidity +=  humidityRounding;
    //normalizing output
    float normalizedHumidity = abs(humidity - normalHumidity);
    // blinks count and mode
    inverseBlinks = humidity < normalHumidity;
    int blinksCount = normalizedHumidity / humidityPercentsPerBlink;
    // negative blinks must be ceil (+0.5 -> 0, -0.5 -> 1)
    if (inverseBlinks) blinksCount += 1;
//    Serial.println(blinksCount);
    
    blinkDigit(blinksCount);
  }
}

void pause() {
//  digitalWrite(led, HIGH);
  delay(1000);
//  digitalWrite(led, LOW);
}

void blink(int time1, int time2) {
  int blinkState, unblinkState;
  blinkState = inverseBlinks ? LOW : HIGH;
  unblinkState = inverseBlinks ? HIGH : LOW;
  digitalWrite(led, blinkState);
  delay(time1);
  //Serial.print(0);
  digitalWrite(led, unblinkState);
  delay(time2);
}

void shortBlink() {
  blink(100, 100);
}
void longBlink() {
  blink(150, 200);
}

void blink(int times){
  for (int i = 0; i < times; i++)
    shortBlink();
  delay(300);
}
void tripleBlink(int times) {
  for (int i = 0; i < times; i++) 
    blink(3);
}
void doubleBlink(int times) {
  for (int i = 0; i < times; i++) 
    blink(2);
}
void singleBlink(int times) {
  for (int i = 0; i < times; i++) 
    longBlink();
}

void blinkDigit(int digit) {
  int doubleBlinks = 0;
  int tripleBlinks = 0;
  int singleBlinks = 0;
  //Serial.print(" blinking ");
  //Serial.println(digit);
  if (digit < 3) {
    if (digit == 2) {
      singleBlinks = 0;
      doubleBlinks = 1;
    }
    else if (digit == 1) {
      singleBlinks = 1;
      doubleBlinks = 0;
    }
  }
  else {
    int rest = digit % 3;
    if ( rest == 0) {
      singleBlinks = 0;
      doubleBlinks = 0;
    }
    else if ( rest == 1) {
      singleBlinks = 0;
      doubleBlinks = 2;
    }
    else if (digit % 3 == 2) {
      singleBlinks = 0;
      doubleBlinks = 1;
    }
  }
  tripleBlinks = (digit - doubleBlinks*2) / 3;
  
  //Serial.print(" blinking triples: " );
  //Serial.println( tripleBlinks);
  //  Serial.print(" blinking doubles: " );
  //Serial.println( doubleBlinks);
  //Serial.print(" blinking singles: " );
  //Serial.println( singleBlinks);

  tripleBlink(tripleBlinks);
  doubleBlink(doubleBlinks);
  singleBlink(singleBlinks);
  //Serial.println();
  
}
