#include <MyoController.h>

#define RM 2
#define LM 1
#define STEER 0
#define CENT 512
#define RI 0
#define LE 1023

//TODO
// define globals that are incremented/decremented by switchcase

MyoController myo = MyoController();
String pose = "";

void setup() {
  pinMode(RM, OUTPUT);
  pinMode(LM ,OUTPUT);
  pinMode(STEER, OUTPUT);
  
  myo.initMyo();
}

void loop()
{
   //Serial.println("HI");
   myo.updatePose();
   
   switch ( myo.getCurrentPose() ) {
    case rest:
      analogWrite(STEER, CENT);
      break;
    case doubleTap:
      break;
   case fist:
      analogWrite(STEER, CENT);
      digitalWrite(LM, LOW); 
      digitalWrite(RM,LOW);
      
      break;
    case waveIn:
      analogWrite(STEER, LE); 
      break;
    case waveOut:
      analogWrite(STEER, RI); 
      break;
    case fingersSpread:
      analogWrite(STEER, CENT);
      digitalWrite(LM, HIGH); 
      digitalWrite(RM, HIGH);
      break;

   } 
   delay(100);
}
