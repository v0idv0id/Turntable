// Copyright (C) 2016 Martin Willner

#include <AccelStepper.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

int runStepper =1;
int runStepper2 = 1;

int speedStepper = 50;
int speedStepper2 = 25;
int moveStepper = 100;
int moveStepper2 = 100;
int accelStepper=4000;
int accelStepper2=2000;

char keys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {9,8,7,6}; 
byte colPins[COLS] = {10,11,12,13}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



AccelStepper stepper(1,3,2); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(1,5,4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5


void setup()
{  
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  
  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(speedStepper); //50 is ok!
  stepper.setAcceleration(accelStepper); //1000 is ok
  stepper.moveTo(moveStepper);
  stepper2.setMaxSpeed(speedStepper2); //50 is ok!
  stepper2.setAcceleration(accelStepper); //1000 is ok
  stepper2.moveTo(moveStepper2);
  Serial.begin(9600); 

}

void loop()
{
    char key = keypad.getKey();

      if (key) {
        //Serial.println(key);
    }

    // If at the end of travel go to the other end
if(runStepper) {
    stepper.run();
}

    if (stepper.distanceToGo() == 0) {
        int p = stepper.currentPosition();
        stepper.moveTo(-p);
    }
    
if(runStepper2) {
    stepper2.run();
}

    if (stepper2.distanceToGo() == 0) {
      stepper2.moveTo(-stepper2.currentPosition());
    }

}





void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case HOLD:
        if (key == '4') {
            speedStepper=50; 
              stepper.setMaxSpeed(speedStepper);
            Serial.print("Stepper 1 - Speed :");
             Serial.println(speedStepper);


        }

        if (key == '5') { 
              speedStepper2=25; 
              stepper2.setMaxSpeed(speedStepper2);
              
 Serial.print("Stepper 2 - Speed :");
             Serial.println(speedStepper2);


        }
      if(key=='8') {
          moveStepper=50; 
          
          stepper.moveTo(moveStepper);
           Serial.print("Stepper 1 - MoveTo :");
             Serial.println(moveStepper);

        }

          if(key=='9') { 
          moveStepper2=50; 
          stepper2.moveTo(moveStepper2);
          Serial.print("Stepper 2 - MoveTo :");
             Serial.println(moveStepper2);

        }


      if(key=='C') {
        accelStepper=4000; 
          stepper.setAcceleration(accelStepper);
           Serial.print("Stepper 1 - Accel :");
             Serial.println(accelStepper);

        }

          if(key=='D') { accelStepper2=2000; 
         stepper2.setAcceleration(accelStepper2);
          Serial.print("Stepper 2 - Accel :");
             Serial.println(accelStepper2);

        }
  break;


    
    case PRESSED:
        if (key == '0') {
            runStepper = !runStepper;
             Serial.print("Stepper 1 - Mode :");
             Serial.println(runStepper);
        }

        if (key == '1') {
            runStepper2 = !runStepper2;
            Serial.print("Stepper 2 - Mode :");
             Serial.println(runStepper2);

        }


        if (key == '4') {
            speedStepper += 50 ;
            if(speedStepper>1000) { speedStepper=50; }
              stepper.setMaxSpeed(speedStepper);
                stepper.setAcceleration(accelStepper); //1000 is ok
                  Serial.print("Stepper 1 - Speed :");
             Serial.println(speedStepper);


        }

        if (key == '5') {
          speedStepper2 += 25 ;
            if(speedStepper2>1000) { speedStepper2=25; }
              stepper2.setMaxSpeed(speedStepper2);
              stepper2.setAcceleration(accelStepper2); //1000 is ok
 Serial.print("Stepper 2 - Speed :");
             Serial.println(speedStepper2);


        }
      if(key=='8') {
        moveStepper +=100;
         if(moveStepper > 2000) { moveStepper=50; }
          stepper.moveTo(moveStepper);
           Serial.print("Stepper 1 - MoveTo :");
             Serial.println(moveStepper);

        }

          if(key=='9') {
        moveStepper2 +=50;
         if(moveStepper2 > 1000) { moveStepper2=50; }
         stepper2.moveTo(moveStepper2);
          Serial.print("Stepper 2 - MoveTo :");
             Serial.println(moveStepper2);

        }


      if(key=='C') {
        accelStepper +=100;
         if(accelStepper > 4000) { accelStepper=100; }
          stepper.setAcceleration(accelStepper);
           Serial.print("Stepper 1 - Accel :");
             Serial.println(accelStepper);

        }

          if(key=='D') {
        accelStepper2 +=100;
         if(accelStepper2 > 2000) { accelStepper2=100; }
         stepper2.setAcceleration(accelStepper2);
          Serial.print("Stepper 2 - Accel :");
             Serial.println(accelStepper2);

        }
break;


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

