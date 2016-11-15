//
// Created by swanta on 15.11.16.
//

#ifndef ARDUINO_TEST_H
#define ARDUINO_TEST_H

const enum MODE {INPUT = 'INPUT', OUTPUT = 'OUTPUT'};
const enum SIGNAL {LOW, HIGH};
void pinMode(int, MODE);
SIGNAL digitalRead(int);
void digitalWrite(int, SIGNAL);

#endif //ARDUINO_TEST_H
