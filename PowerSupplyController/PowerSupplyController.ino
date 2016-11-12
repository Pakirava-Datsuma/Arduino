	//pins
	enum pin { 
		pinInControlButton = 5;
		pinInControlComp = 6;
		pinInControlNormalMode = 7;
		pinInControlHeadset = 8;
		pinInDefenceIpositive1 = ;
		pinInDefenceInegative1 = ;
		pinInDefenceIpositive2 = ;
		pinInDefenceInegative2 = ;
		pinInDefenceA1 = ;
		pinInDefenceA2 = ;

		pinOutControlAmplifierEnable = ;
		pinOutControlAmplifierPower = ;
		pinOutControlHeadsetPower = ;
		pinOutControlSleepMode = ;
		pinOutIndicateStandByModeNormal = ;
		pinOutIndicateStandByModeNotNormal = ;
		pinOutIndicateHeadsetMode = ;
		pinOutErrorI1 = ;
		pinOutErrorI2 = ;
		pinOutErrorA1 = ;
		pinOutErrorA2 = ;
	}
	
	volatile bool ledNotNormalMode;
	volatile bool ledHeadsetMode;
	
	Modes modes;
			
void setup() {
	pinMode(pinInControlNormalMode, DIGITAL);
	pinMode(pinIsCompOn, DIGITAL);
	
	modes = new Modes();	
}

void loop() {
	modes::processCurrentMode();
}

class Modes {
public:	
	Modes () {}
	
	void process() {
		checkIO();
		currentMode::process();
	}

protected:
	static Mode currentMode;
	static Mode normalMode = new NormalMode();
	static Mode sleepMode = new SleepMode();
	static Mode standByMode = new StandByMode();
	static Mode failureMode = new FailureMode();

	static bool isNormalModeRequested;
	static bool isCompOn;
	static bool isHeadsetRequested;
	

	void changeMode (Mode newMode) {
		isModeChanged = (currentMode != newMode);
		if (isModeChanged) {
			detachInterrupts();
			if (currentMode != null) currentMode::finalize();
			currentMode = newMode;
			currentMode::initialize();
			attachInterrupts();
		}
	}

	class Mode {
		virtual void initialize();
		virtual void process();
		virtual void finalize();
	}

	class NormalMode : Mode {
		
		NormalMode () {
		}
		void initialize () {
//			HeadsetLED
//			HeadsetButton
			attachInterrupt(digitalPinToInterrupt(pinInControlHeadset), ISR_AudioOutput, FALLING);
			
//			ModeButton
			attachInterrupt(digitalPinToInterrupt(pinInControlButton), ISR_Sleep, FALLING);
		}
		void process() {
			if (isHeadsetButtonPressed) changeHeadsetMode(!isHeadsetRequested);
			if (isFailure) changeMode(failureMode);
			if (isPowerButtonPressed) changeMode(standByMode);		
		}
		void finalize() {
			
		}
		void ISR_AudioOutput() {
			digitalWrite(pinOutIndicateHeadsetMode, 
				ledHeadsetMode ? HIGH : LOW
				);
			ledHeadsetMode = !ledHeadsetMode;
		}
		void ISR_Sleep() {
			}
	}

	class SleepMode : Mode {
		
		final int timeLedOn = 3000;
		final int timeLedOff = 3000;
		
		SleepMode () {
		}
		
		void initialize () {
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
		
		void process() {
			if (isPowerButtonPressed) changeMode(normalMode);
		}
		void finalize() {}
		void ISR_ButtonWhenSlept () {
			changeMode(normalMode);
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
		
	}

	class StandByMode : Mode {
		StandByMode () {}
		void initialize () {
			digitalWrite(pinOutControlSleepMode, LOW);
			digitalWrite(pinOutIndicateStandByModeNormal, LOW);
			digitalWrite(pinOutControlAmplifierEnable, LOW);
			digitalWrite(pinOutControlAmplifierPower, LOW);
			digitalWrite(pinOutControlHeadsetPower, LOW);	
		}
		void process() {
			if (isPowerButtonPressed) changeMode(modeNormal);
		}
		void finalize() {}
	}
	class FailureMode : Mode {
		FailureMode () {}
		void initialize () {
			ISR_FailureModeBlink();
		}
		void process() {
			wait(timeFailureWait);
			if (checkDefenceInputs())
				sleepAfterFailure();
			else
				changeMode(NormalMode);
		}
		void finalize() {}
		void ISR_FailureModeBlink() {
			
		}
	}
	/*
	class FailureMode : Mode {
		FailureMode () {}
		void initialize () {}
		void process() {}
		void finalize() {}
	}
	*/
}
