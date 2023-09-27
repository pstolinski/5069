/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\tkashyap723                                      */
/*    Created:      Mon Nov 15 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FR                   motor         11              
// FL                   motor         12              
// BR                   motor         13              
// BL                   motor         14              
// Tread                motor         18              
// MotorGroup1          motor_group   17, 16          
// DigitalOutC          digital_out   C               
// DigitalOutB          digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;

int tradSpeed = 100;
int lifSpeed = 25;
int y = 0;
int x = 0;
bool on = false;

void autonomous(){
   FR.spin(reverse, 100, pct);
   FL.spin(reverse, 80, pct);
   BR.spin(reverse, 100, pct);
   BL.spin(reverse, 80, pct);
   MotorGroup1.spin(forward, 100, pct);
   wait(250, msec);
   MotorGroup1.setVelocity(0, percent);
   MotorGroup1.setStopping(hold);
   wait(2300, msec);
   FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   DigitalOutB.set(false);
   DigitalOutC.set(true);
   FR.spin(forward, 100, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 100, pct);
   BL.spin(forward, 100, pct);
   wait(2000, msec);
   FR.spin(reverse, 100, pct);
   FL.spin(reverse, -100, pct);
   BR.spin(reverse, 100, pct);
   BL.spin(reverse, -100, pct);
   wait(1250, msec);
   DigitalOutB.set(true);
   DigitalOutC.set(false);
   FR.spin(reverse, 100, pct);
   FL.spin(reverse, 100, pct);
   BR.spin(reverse, 100, pct);
   BL.spin(reverse, 100, pct);
   wait(1250, msec);
   FR.spin(reverse, -100, pct);
   FL.spin(reverse, 100, pct);
   BR.spin(reverse, -100, pct);
   BL.spin(reverse, 100, pct);
}

void drive(){
  FR.spin(forward, Controller1.Axis2.position(pct), pct);
  FL.spin(forward, Controller1.Axis3.position(pct), pct);
  BR.spin(forward, Controller1.Axis2.position(pct), pct);
  BL.spin(forward, Controller1.Axis3.position(pct), pct);
}

int treadSpeed(){
  if(Controller1.ButtonDown.pressing()){
    return -100;
  }
  else if(Controller1.ButtonUp.pressing()){
    return 100;
  }
  else{
    return 0;
  }
}

void tread(){
  Tread.spin(fwd, treadSpeed(), pct);
}

int liftSpeed(){
  if(Controller1.ButtonL1.pressing()){
    return 25;
  }
  else if(Controller1.ButtonL2.pressing()){
    return -25;
  }
  else{
    return 0;
  }
}

void lift(){
  MotorGroup1.spin(forward, liftSpeed(), pct);
}

void flick(){
  if(Controller1.ButtonY.pressing()){
    MotorGroup1.spin(forward, 100, pct);
  }
}

void userControl(){
  vexcodeInit();
  MotorGroup1.setStopping(hold);
  while(true){
  flick();
  drive();
  tread();
  lift();
  }
}
//if(Controller1.ButtonA.pressing()){
//      if(on == true){
//        DigitalOutB.set(false);
//        DigitalOutC.set(false);
//        on = false;
//      }else if(on == false){
//        DigitalOutB.set(true);
//        DigitalOutC.set(true);
//        on = true;
//      }
//      waitUntil(!Controller1.ButtonA.pressing());
//    }
int main(){
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);

  while (true) {
    wait(100, msec);
  }
}
