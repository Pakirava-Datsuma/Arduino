	//pins
	enum class pins {
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

    class Controller {
	public:
        Controller();
        class Mode {
			Controller* controller;
			Mode(Controller* controller): controller(controller) {};
            virtual void initialize();
            virtual void process();
            virtual void finalize();
        };

        bool isNormalModeRequested;
		bool isCompOn;
		bool isHeadsetRequested;

		bool checkIO();

		void process();
		void changeMode(Mode*);


        class NormalMode;
        class SleepMode;
        class FailureSleepMode;
        class StandByMode;
        class FailureMode;

		volatile bool ledNotNormalMode;
		volatile bool ledHeadsetMode;

		Mode *currentMode;
		Mode *normalMode;
		Mode *sleepMode;
		Mode *standByMode;
		Mode *failureMode;
		Mode *failureSleepMode;
	};

	Controller *controller;

	void setup() {

    	controller = new Controller();


	};

void loop() {
	controller*::process();
};
/*
void main()
{
    setup();
    while (1)
    {
        loop();
    }
};
*/
    Controller::Controller() {
		normalMode = new NormalMode(this);
		sleepMode = new SleepMode(this);
		standByMode = new StandByMode(this);
		failureMode = new FailureMode(this);
		failureSleepMode = new FailureSleepMode(this);

		for (pins &&pin :pins) {
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

    void Controller::process() {
        readInputs();
        currentMode*::process();
    };


    void Controller::changeMode(Controller::Mode* newMode) {
        bool isModeChanged = *currentMode != *newMode;
        if (isModeChanged) {
            detachInterrupts();
            if (currentMode != null) currentMode*::finalize();
            currentMode = newMode;
            currentMode*::initialize();
            attachInterrupts();
        }
    };

	class NormalMode : Controller::Mode {

		void initialize () {
//			HeadsetLED
//			HeadsetButton
			attachInterrupt(digitalPinToInterrupt(pins::InControlHeadset), ISR_AudioOutput, FALLING);
			
//			ModeButton
			attachInterrupt(digitalPinToInterrupt(pins::InControlButton), ISR_Sleep, FALLING);
		}
		void process() {
			if (isHeadsetButtonPressed) changeHeadsetMode(!isHeadsetRequested);
			if (isFailure) controller*::changeMode(failureMode);
			if (isPowerButtonPressed) controller*::changeMode(standByMode);
		}
		void finalize() {
			
		}
		void ISR_AudioOutput() {
			digitalWrite(pins::OutIndicateHeadsetMode, 
				ledHeadsetMode ? HIGH : LOW
				);
			ledHeadsetMode = !ledHeadsetMode;
		}
		void ISR_Sleep() {
			}
	};

	class SleepMode : Controller::Mode {
		
		final int timeLedOn = 3000;
		final int timeLedOff = 3000;

		void initialize () {
			//interrupts
			attachInterrupt(digitalPinToInterrupt(pins::InControlButton), ISR_ButtonWhenSlept, FALLING);
			ISR_SleepModeLEDBlink();
			//Output
			digitalWrite(pins::OutControlSleepMode, HIGH);
			digitalWrite(pins::OutIndicateStandByModeNormal, LOW);
			digitalWrite(pins::OutControlAmplifierEnable, LOW);
			digitalWrite(pins::OutControlAmplifierPower, LOW);
			digitalWrite(pins::OutControlHeadsetPower, LOW);
		}
		
		void process() {
			if (isPowerButtonPressed) controller*::changeMode(normalMode);
		}
		void finalize() {}
		void ISR_ButtonWhenSlept () {
			controller*::changeMode(normalMode);
		}
		void ISR_SleepModeBlink () {
			digitalWrite(pins::OutIndicateStandByModeNormal, 
				ledNotNormalMode ? HIGH : LOW
				);
			ledNotNormalMode = !ledNotNormalMode;
			attachInterrupt(timer, ISR_SleepModeLEDBlink, 
				ledNotNormalMode ? timeLedOnSleepMode : timeLedOffSleepMode
				);
		}
		
	};

	class FailureSleepMode : Controller::SleepMode {
          void initialize () {
			  SleepMode::initialize();
			  FailureMode::ISR_FailureModeBlink();
          }
    };

	class StandByMode : Controller::Mode {
		void initialize () {
			digitalWrite(pins::OutControlSleepMode, LOW);
			digitalWrite(pins::OutIndicateStandByModeNormal, LOW);
			digitalWrite(pins::OutControlAmplifierEnable, LOW);
			digitalWrite(pins::OutControlAmplifierPower, LOW);
			digitalWrite(pins::OutControlHeadsetPower, LOW);	
		};
		void process() {
			if (isPowerButtonPressed) controller*::changeMode(normalMode);
		};
		void finalize() {};
	};
	class FailureMode : Controller::Mode {
		void initialize () {
			ISR_FailureModeBlink();
		}
		void process() {
			wait(timeFailureWait);
			if (checkDefenceInputs())
				controller*::changeMode(failureSleepMode);
			else
				controller*::changeMode(normalMode);
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

