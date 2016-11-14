  int buttons[] = {1,2,3,5};
  int outs[] = {6,7};
  int outSignal[] = {0, 0};

int currentSignalPinIndex = 0;

void setup() {
  for (int p = 0; p < 4; p++)
    pinMode(buttons[p], INPUT);
  for (int p = 0; p < 2; p++)
    pinMode(outs[p], OUTPUT);
  
}

void loop(){
  int newSignalPinIndex = 0;
  
  for (int p = 0; p < 4; p++)
  {
    if ((p != currentSignalPinIndex) && (digitalRead(buttons[p]) == HIGH))
        newSignalPinIndex = p;
       
  }
  
  if (newSignalPinIndex > 0)
  {
    if (currentSignalPinIndex > 0) pinMode(buttons[currentSignalPinIndex], INPUT);
    
    pinMode(buttons[newSignalPinIndex], OUTPUT);
    digitalWrite(buttons[newSignalPinIndex], HIGH);
    outSignal[0] = (newSignalPinIndex > 1) ? HIGH : LOW;
    outSignal[1] = (newSignalPinIndex % 2 == 0) ? HIGH : LOW;
    for (int p = 0; p < 2; p++)
      digitalWrite(outs[p], outSignal[p]);
    
    currentSignalPinIndex = newSignalPinIndex;
  }
}
