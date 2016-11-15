//
// Created by swanta on 15.11.16.
//
#include <std>
#include "test.h"
#include "../Selector/Selector.ino"
using namespace std;

unsigned int const numberOfLoops = 3;

int main () {
    setup();
    for (int i = 0; i < numberOfLoops; ++i)
        loop();
    return 0;
};

struct Pin
{
    MODE mode;
    SIGNAL state;
};

Pin pins[] = new Pin[20];

void pinMode(int pin, MODE mode)
{
    pins[pin].mode = mode;
    printf("switching pin mode %s%d\n", (mode == INPUT ? "=>" : "<="), pin);
};

void checkPinMode(int pin, MODE mode)
{
    static const string msgUndefined = "Pin mode isn't SET !";
    static const string msgUnmatch = "Pin mode isn't MATCH !";
    static const string msgTemplate = "\nERROR on pin %d\n%s\n\n";

    string msg = "";

    if (pins[pin].state == UNDEFINED)
        msg = msgUndefined;
    else if (pins[pin].state != mode)
        msg = msgUnmatch;

    if (msg != "")
        printf(msgTemplate, pin, msg);
};

SIGNAL digitalRead(int pin)
{
    checkPinMode(pin, OUTPUT);
    printf("Enter new signal for pin %d : ", pin);
    cin >> pins[pin].state;
    return pins[pin].state;
};

void digitalWrite(int pin, SIGNAL signal)
{
    checkPinMode(pin, OUTPUT);
    printf("OUTPUT signal from pin %d : %d", pin, signal);
};

