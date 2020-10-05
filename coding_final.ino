#define NORTH 1
#define SOUTH 2
#define OFF 0

char pins[] = {12, 3, 9, 13, 11, 8};
int pinLength = 6;
int buttonPin = 2;

/*
 * Coil A 12, 3
 * 
 * Coil B 13, 11
 * 
 */


void setup() {
  for(int i = 0; i < pinLength; i++){
    pinMode(pins[i], OUTPUT);
  }
  pinMode(buttonPin, input);
  shutDown();
  Serial.begin(9600);
}



bool buttonPushStart = false;;
bool finishedSequence = false;
bool startedSequence = false;
bool hitButton = false;


/*
 * Based on calculation that 200 steps = 8mm
 * 
 * We know that 200 steps = 50 fullClockWise calls
 * so 50 * 5/8 = 5_mm_outward;
 * 
 * 
 */
int 5_mm_outward = 31;

int buttonState = 0;

void loop() {
  buttonState = digitalRead(buttonPin);
  //Checking to see if the sequence is over
  if(!finishedSequence){
    //Checking to see if we started moving yet
    if(!startedSequence){
       //Checking if button got pushed for first time to start moving.
      if(buttonState == 1){
        started = true;
      }
    }
    //If homing has started
    else{
      //If the homing hasn't found the button
      if(!hitButton){
        fullClockise(1500);
      }
      // This is now a calculated sequence
      else{
        //Moving out 5mm at LOW speed
        for(int i = 0; i < 5_mm_outward; i++){
          fullCounter(5000);        
        }
        //Moving back in 5mm at LOW speed half step
        for(int j = 0; j < 5_mm_outward; i++){
          halfClockwise(5000);
        }
        //Moving back out 20mm at LOW speed half step
        for(int k = 0; k < 5_mm_outward * 4; k++){
          halfCounter(5000);
        }
        finishedSequence = true;
      }
    }
  //Adding slight delay to be able to read the button
  delay(10);    
  }
  

 

  shutDown();
  while(true){
    
  }

}

void halfCounter(int delayMicro){
  coilB(SOUTH);
  coilA(OFF);
  delayMicroseconds(delayMicro);

  coilA(SOUTH);
  coilB(SOUTH);

  delayMicroseconds(delayMicro);

  coilA(SOUTH);
  coilB(OFF);

  delayMicroseconds(delayMicro);

  coilA(SOUTH);
  coilB(NORTH);

  delayMicroseconds(delayMicro);

  coilA(OFF);
  coilB(NORTH);

  delayMicroseconds(delayMicro);

  coilA(NORTH);
  coilB(NORTH);

  delayMicroseconds(delayMicro);

  coilA(NORTH);
  coilB(OFF);

  delayMicroseconds(delayMicro);

  coilA(NORTH);
  coilB(SOUTH);

  delayMicroseconds(delayMicro);

}

void halfClockwise(int delayMicro){
  coilB(SOUTH);
  coilA(OFF);
  delayMicroseconds(delayMicro);

  coilA(NORTH);
  coilB(SOUTH);

  delayMicroseconds(delayMicro);

  coilA(NORTH);
  coilB(OFF);

  delayMicroseconds(delayMicro);

  coilA(NORTH);
  coilB(NORTH);

  delayMicroseconds(delayMicro);

  coilA(OFF);
  coilB(NORTH);

  delayMicroseconds(delayMicro);

  coilA(SOUTH);
  coilB(NORTH);

  delayMicroseconds(delayMicro);

  coilA(SOUTH);
  coilB(OFF);

  delayMicroseconds(delayMicro);

  coilA(SOUTH);
  coilB(SOUTH);

  delayMicroseconds(delayMicro);

}


void fullClockwise(int delayMicro){
  coilB(OFF);
  coilA(NORTH);
  delayMicroseconds(delayMicro);

  coilA(OFF);
  coilB(NORTH);

  delayMicroseconds(delayMicro);

  coilA(SOUTH);
  coilB(OFF);

  delayMicroseconds(delayMicro);

  coilA(OFF);
  coilB(SOUTH); 
  delayMicroseconds(delayMicro);
}

void fullCounter(int delayMicro){
  coilB(OFF);
  coilA(SOUTH);
  delayMicroseconds(delayMicro);

  coilA(OFF);
  coilB(NORTH);

  delayMicroseconds(delayMicro);

  coilA(NORTH);
  coilB(OFF);

  delayMicroseconds(delayMicro);

  coilA(OFF);
  coilB(SOUTH); 
  delayMicroseconds(delayMicro);
}

void coilA(int polarity){
  if(polarity == NORTH){
    digitalWrite(12, HIGH);
    digitalWrite(3, HIGH);
  }else if(polarity == SOUTH){
    digitalWrite(12, LOW);
    digitalWrite(3, HIGH);
  }else if(polarity == OFF){
    digitalWrite(12, OFF);
    digitalWrite(3, OFF);
  }
}

void coilB(int polarity){
  if(polarity == NORTH){
    digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);
  }else if(polarity == SOUTH){
    digitalWrite(13, LOW);
    digitalWrite(11, HIGH);
  }else if(polarity == OFF){
    digitalWrite(13, OFF);
    digitalWrite(11, OFF);
  }
}



void shutDown(){
  for(int i = 0; i < pinLength; i++){
    digitalWrite(pins[i], LOW);
  }
}
