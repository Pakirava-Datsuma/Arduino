enum class pins 
{
  button1 = 1,
  button2 = 2,
  button3 = 3,
  button4 = 5,
  
  out1 = 6,
  out2 = 7
};

int currentPin = 0;

void setup() {
  for (pins &&pin: pins)
  {
    pinMode(ledPin, DIGITAL);
  }
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}
