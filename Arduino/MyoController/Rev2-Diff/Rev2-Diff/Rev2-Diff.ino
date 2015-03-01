#include <MyoController.h>

#define RM 3
#define LM 9
#define MIN_GATE 0//(255/5*1.25)
#define MAX_GATE 250// (255/5*3)
#define FREQ 100

MyoController myo = MyoController();
String pose = "";
int LMC = MIN_GATE;
int RMC = MIN_GATE;
int st = 10;//(MAX_GATE-MIN_GATE)/(FREQ*3);

void turnL(){
  LMC = MIN_GATE;
  RMC = MAX_GATE;
}
void turnR(){
    LMC = MAX_GATE;
    RMC = MIN_GATE;
}

void accel(){
  if (LMC < MAX_GATE) {
    LMC = RMC = LMC + st;
  }
}

void brake(){
if (LMC > MIN_GATE) {
    LMC = RMC = LMC - st;
  }
}

void setup() {
  pinMode(RM , OUTPUT);
  pinMode(LM , OUTPUT);
  myo.initMyo();
  digitalWrite(LM, LOW);
  digitalWrite(RM, LOW);
  

}

void loop()
{
     myo.updatePose();
     switch ( myo.getCurrentPose() ) {
      case rest:
        break;
      case doubleTap:
        break;
     case fist:
        brake();
        break;
      case waveIn: //Turn Left
        turnL();
        break;
      case waveOut: //Turn Right
        turnR();
        break;
      case fingersSpread:
        accel();
        break;
     }

     analogWrite(LM, LMC);
     analogWrite(RM, RMC);
     delay(100);

   
}
