// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Clamp                motor         8               
// HiLift               motor_group   16, 6           
// VisionSensor         vision        11              
// FL                   motor         19              
// FR                   motor         9               
// BL                   motor         20              
// BR                   motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;
int VisionSensor_objectIndex = 0;

float myVariable;

event message1 = event();
int centerFOV = 158;
int offsetX = 15;
// "when started" hat block
int whenStarted1() {
  while (true) {
    VisionSensor.takeSnapshot(VisionSensor__SIG_RED);
    
      if (VisionSensor.objects[0].centerX > centerFOV + offsetX) {
        FL.spin(forward, 100, pct);
        BL.spin(forward, 100, pct);
        FR.spin(reverse, 100, pct);
        BR.spin(reverse, 100, pct);
      }
      if (VisionSensor.objects[0].centerX < centerFOV - offsetX) {
        FL.spin(reverse, 100, pct);
        BL.spin(reverse, 100, pct);
        FR.spin(forward, 100, pct);
        BR.spin(forward, 100, pct);
      }
      if (VisionSensor.objects[0].centerX > centerFOV + offsetX && VisionSensor.objects[0].centerX < centerFOV - offsetX) {
        if (VisionSensor.objects[0].width < 125.0) {
          FL.spin(forward, 100, pct);
          BL.spin(forward, 100, pct);
          FR.spin(forward, 100, pct);
          BR.spin(forward, 100, pct);
        }
        else {
          FR.stop();
          BR.stop();
          BL.stop();
          FL.stop();
        }
    }
    else {
      FL.spin(forward, 100, pct);
      BL.spin(forward, 100, pct);
      FR.spin(reverse, 100, pct);
      BR.spin(reverse, 100, pct);
    }
  //wait(5, msec);
  }
  //return 0;
}


int main() {
  // post event registration

  // set default print color to black
  //printf("\033[30m");

  // wait for rotation sensor to fully initialize
  //wait(30, msec);

  whenStarted1();
}