#define NORTH 1
#define SOUTH 2
#define OFF 0

char pins[] = {12, 3, 9, 13, 11, 8};
int pinLength = 6;

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
  shutDown();
  Serial.begin(9600);
}

void loop() {

  for(int i = 0; i < 400; i++){
    motorHalf(2000);
  }
  // put your main code here, to run repeatedly:

  shutDown();
  while(true){
    
  }

}

void motorHalf(int delayMicro){
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


void motorSequence(int delayMicro){
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
