#include <MyoController.h>

#define RM 9
#define LM 3
#define MIN_GATE 0//(255/5*0.95)
#define MAX_GATE (255/5*3)
#define FREQ 100

MyoController myo = MyoController();
String pose = "";
int LMC = MIN_GATE;
int RMC = MIN_GATE;
int a = LMC;
int b = RMC;
int st = 30;//(MAX_GATE - MIN_GATE) / (FREQ * 3);
int stB = 60;

void turnL() {
  if (LMC == RMC) {
    a = b = LMC;
  }

  LMC = MIN_GATE;
  RMC = MAX_GATE;
}
void turnR() {
  if (LMC == RMC) {
    a = b = LMC;
  }
  LMC = MAX_GATE;
  RMC = MIN_GATE;
}

void accel() {
  if (LMC < MAX_GATE - st) {
    a = b = LMC = RMC = LMC + st;
  }
}

void brake() {
  if ((LMC > MIN_GATE + stB) || (RMC > MIN_GATE + stB)) {
    if (LMC > RMC) {
      a = b = LMC = RMC = LMC - stB;
    }
    else
    {
      a = b = LMC = RMC = RMC - st;
    }
  }
  else {
    a = b = LMC = RMC = MIN_GATE;
  }
}

void setup() {
  pinMode(RM , OUTPUT);
  pinMode(LM , OUTPUT);
  myo.initMyo();
  analogWrite(LM, MIN_GATE);
  analogWrite(RM, MIN_GATE);
  //  digitalWrite(LM, LOW);
  // digitalWrite(RM, LOW);
}

void loop()
{
  myo.updatePose();
  switch ( myo.getCurrentPose() ) {
    case rest:
      LMC = a;
      RMC = b;
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
