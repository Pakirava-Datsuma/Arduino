	//pins
	enum class pin {
		InControlButton = 5,
		InControlComp = 6,
		InControlNormalMode = 7,
		InControlHeadset = 8,
		InDefenceIpositive1,
		InDefenceInegative1,
		InDefenceIpositive2,
		InDefenceInegative2,
		InDefenceA1,
		InDefenceA2,

		OutControlAmplifierEnable  ,
		OutControlAmplifierPower  ,
		OutControlHeadsetPower  ,
		OutControlSleepMode  ,
		OutIndicateStandByModeNormal  ,
		OutIndicateStandByModeNotNormal  ,
		OutIndicateHeadsetMode  ,
		OutErrorI1  ,
		OutErrorI2  ,
		OutErrorA1  ,
		OutErrorA2  ,
	};
	
	volatile bool ledNotNormalMode;
	volatile bool ledHeadsetMode;

	Modes* modes;
			
void setup() {

	
	modes = new Modes();	
}

void loop() {
	modes::processCurrentMode();
}

class Modes {
public:
    void Modes();

    void changeMode(Mode newMode);

protected:
    static Mode currentMode;
    static Mode normalMode = new NormalMode();
    static Mode sleepMode = new SleepMode();
    static Mode standByMode = new StandByMode();
    static Mode failureMode = new FailureMode();

    static bool isNormalModeRequested;
    static bool isCompOn;
    static bool isHeadsetRequested;

    bool checkIO();

    void process();

    class Mode;

    class NormalMode;

    class SleepMode;
    
    class FailureSleepMode;

    class StandByMode;

    class FailureMode;
};

    void Modes::Modes() {
        for (auto &&pin :pins) {
            pinMode(pin, DIGITAL);
        }
/*        pinMode(pin::InControlNormalMode, DIGITAL);
        pinMode(pin::InControlComp, DIGITAL);
        pinMode(pin::InControlButton, DIGITAL);
        pinMode(pin::InControlComp, DIGITAL);
        pinMode(pin::InControlNormalMode, DIGITAL);
        pinMode(pin::InControlHeadset, DIGITAL);
        pinMode(pin::InDefenceIpositive1, DIGITAL);
        pinMode(pin::InDefenceInegative1, DIGITAL);
        pinMode(pin::InDefenceIpositive2, DIGITAL);
        pinMode(pin::InDefenceInegative2, DIGITAL);
        pinMode(pin::InDefenceA1, DIGITAL);
        pinMode(pin::InDefenceA2, DIGITAL);
        pinMode(pin::OutControlAmplifierEnable  , DIGITAL);
        pinMode(pin::OutControlAmplifierPower  , DIGITAL);
        pinMode(pin::OutControlHeadsetPower  , DIGITAL);
        pinMode(pin::OutControlSleepMode  , DIGITAL);
        pinMode(pin::OutIndicateStandByModeNormal  , DIGITAL);
        pinMode(pin::OutIndicateStandByModeNotNormal  , DIGITAL);
        pinMode(pin::OutIndicateHeadsetMode  , DIGITAL);
        pinMode(pin::OutErrorI1  , DIGITAL);
        pinMode(pin::OutErrorI2  , DIGITAL);
        pinMode(pin::OutErrorA1  , DIGITAL);
        pinMode(pin::OutErrorA2, DIGITAL);
*/

        changeMode(normalMode);
    }

    void Modes::process() {
        checkIO();
        currentMode::process();
    }


    void Modes::changeMode(Mode newMode) {
        bool isModeChanged = currentMode != newMode;
        if (isModeChanged) {
            detachInterrupts();
            if (currentMode != null) currentMode::finalize();
            currentMode = newMode;
            currentMode::initialize();
            attachInterrupts();
        }
    }


	class Modes::Mode {
		virtual void initialize();
		virtual void process();
		virtual void finalize();
	};

	class Modes::NormalMode : Mode {
		
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
	};

	class Modes::SleepMode : Mode {
		
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
		
	};

	class Modes::FailureSleepMode : SleepMode {
          void initialize () {
              SleepMode::initialize();
              FailureMode::ISR_FailureModeBlink();
          }
        };

	class Modes::StandByMode : Mode {
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
	};
	class Modes::FailureMode : Mode {
		FailureMode () {}
		void initialize () {
			ISR_FailureModeBlink();
		}
		void process() {
			wait(timeFailureWait);
			if (checkDefenceInputs())
				changeMode(failureSleepMode);
			else
				changeMode(NormalMode);
		}
		void finalize() {}
		void ISR_FailureModeBlink() {
			
		}
	};
	/*
	class FailureMode : Mode {
		FailureMode () {}
		void initialize () {}
		void process() {}
		void finalize() {}
	};
	*/

