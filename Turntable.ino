 // Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

int runStepper =1;
int runStepper2 = 1;

int speedStepper = 1000;
int speedStepper2 = 1000;

char keys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10,11,12,5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



// Define a stepper and the pins it will use
AccelStepper stepper(1,3,2); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(1,13,4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5


void setup()
{  
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  
  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(speedStepper); //50 is ok!
  stepper.setAcceleration(4000); //1000 is ok
  stepper.moveTo(3200);
  stepper2.setMaxSpeed(speedStepper2); //50 is ok!
  stepper2.setAcceleration(4000); //1000 is ok
  stepper2.moveTo(3200);
  

}

void loop()
{
    char key = keypad.getKey();

      if (key) {
        Serial.println(key);
    }

    // If at the end of travel go to the other end
if(runStepper) {
    stepper.run();
}

    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());

if(runStepper2) {
    stepper2.run();
}

    if (stepper2.distanceToGo() == 0)
      stepper2.moveTo(-stepper2.currentPosition());


}





void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        if (key == '0') {
            runStepper = !runStepper;
        }

        if (key == '4') {
            runStepper2 = !runStepper2;

        }


        if (key == '1') {
            speedStepper += 1000 ;
            if(speedStepper>4000) { speedStepper=1000; }
              stepper.setMaxSpeed(speedStepper);
                stepper.setAcceleration(speedStepper); //1000 is ok

        }

        if (key == '5') {
          speedStepper2 += 1000 ;
            if(speedStepper2>4000) { speedStepper2=1000; }
              stepper2.setMaxSpeed(speedStepper2);
                stepper2.setAcceleration(speedStepper2); //1000 is ok


        }

    

}
}
/*
    case RELEASED:
        if (key == 'C') {
            digitalWrite(ledPin,ledPin_state);    // Restore LED state from before it started blinking.
            blink = false;
        }
        break;

    case HOLD:
        if (key == 'C') {
            blink = true;    // Blink the LED when holding the * key.
        }
        break;
    }
    
}
*/

