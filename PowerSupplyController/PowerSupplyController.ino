//const
final int modeNormal = 1;
final int modeStandBy = 2;
final int modeSleep = 3;
final int modeFailure = 4;
final int timeLedOnSleepMode = 3000;
final int timeLedOffSleepMode = 3000;

//pins
final int pinInControlButton = 5;
final int pinInControlComp = 6;
final int pinInControlNormalMode = 7;
final int pinInControlHeadset = 8;
final int pinInDefenceIpositive1 = ;
final int pinInDefenceInegative1 = ;
final int pinInDefenceIpositive2 = ;
final int pinInDefenceInegative2 = ;
final int pinInDefenceA1 = ;
final int pinInDefenceA2 = ;

final int pinOutControlAmplifierEnable = ;
final int pinOutControlAmplifierPower = ;
final int pinOutControlHeadsetPower = ;
final int pinOutControlSleepMode = ;
final int pinOutIndicateStandByModeNormal = ;
final int pinOutIndicateStandByModeNotNormal = ;
final int pinOutIndicateHeadsetMode = ;
final int pinOutErrorI1 = ;
final int pinOutErrorI2 = ;
final int pinOutErrorA1 = ;
final int pinOutErrorA2 = ;

//flags
bool isNormalModeRequested;
bool isCompOn;
bool isHeadsetRequested;

//
volatile bool ledNotNormalMode;
volatile bool ledHeadsetMode;

void setup() {
	pinMode(pinInControlNormalMode, DIGITAL);
	
	pinMode(pinIsCompOn, DIGITAL);
	
	
}

void loop() {
	start:
	
	isNormalModeRequested = (pinRead (inputIsNormalModeRequested) == HIGH);
	isCompOn = (pinRead(pinIsCompOn) == LOW);
	isHeadsetRequested = (pinRead(pinIsHeadsetOn) == LOW);
	isButtonPressed = (pinRead(pinIsButtonPressed) == HIGH);
	
	bool isModeChanged = (mode != oldMode);
	oldMode = mode;
	switch (mode)
	{
		case modeFailure
			failure();
			break;
		case modeNormal
			work(isModeChanged);
			break;
		case modeStandBy
			standBy(isModeChanged);
			break;
		case modeSleep
			sleep(isModeChanged);
			break;
	}
}

void work(bool isNeedInitialize) {
	if (isNeedInitialize)
	{
		
	}
	else
	{
		if (isHeadsetButtonPressed) changeHeadsetMode(!isHeadsetRequested);
		if (isFailure) changeMode(modeFailure);
		if (isPowerButtonPressed) changeMode(modeStandBy);
	}
	
}

void sleep(bool isNeedInitialize) {
	if (isNeedInitialize)
	{
		//interrupts
		attachInterrupt(digitalPinToInterrupt(pinInControlButton), ISR_ButtonWhenSlept, FALLING);
		ISR_SleepModeLEDBlink();
		
		//Output
		digitalWrite(pinOutControlSleepMode, HIGH);
		digitalWrite(pinOutIndicateStandByModeNormal, LOW);
		digitalWrite(pinOutControlAmplifierEnable, LOW);
		digitalWrite(pinOutControlAmplifierPower, LOW);
		digitalWrite(pinOutControlHeadsetPower, LOW);
	}
	else
	{
		if (isPowerButtonPressed) changeMode(modeNormal);
	}
}

void standBy(bool isNeedInitialize) {
	if (isNeedInitialize)
	{
		//interrupts
		ISR_AudioOutput();
		attachInterrupt(digitalPinToInterrupt(pinInControlHeadset), ISR_AudioOutput, FALLING);

		//Outputs
		digitalWrite(pinOutControlSleepMode, LOW);
		digitalWrite(pinOutIndicateStandByModeNormal, LOW);
		digitalWrite(pinOutControlAmplifierEnable, LOW);
		digitalWrite(pinOutControlAmplifierPower, LOW);
		digitalWrite(pinOutControlHeadsetPower, LOW);	

	}
	else
	{
		if (isPowerButtonPressed) changeMode(modeNormal);
		
	}
}

void ISR_SleepModeBlink () {
	digitalWrite(pinOutIndicateStandByModeNormal, 
		ledNotNormalMode ? HIGH : LOW
		);
	ledNotNormalMode = !ledNotNormalMode;
	attachInterrupt(timer, ISR_SleepModeLEDBlink, 
		ledNotNormalMode ? timeLedOnSleepMode : timeLedOffSleepMode
		);
}

void ISR_ButtonWhenSlept () {
	mode = modeNormal
}

void ISR_AudioOutput() {
	digitalWrite(pinOutIndicateHeadsetMode, 
		ledHeadsetMode ? HIGH : LOW
		);
	ledHeadsetMode = !ledHeadsetMode;
}
