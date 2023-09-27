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
// FR                   motor         19              
// FL                   motor         12              
// BR                   motor         20              
// BL                   motor         14              
// Tread                motor         18              
// MotorGroup1          motor_group   17, 16          
// DigitalOutB          digital_out   B               
// DigitalOutA          digital_out   A               
// DriveBooster         motor         10              
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
//bool off = false;

void autonomous(){
  FR.spin(forward, 100, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 100, pct);
   BL.spin(forward, 100, pct);
  MotorGroup1.spin(reverse, 100, pct);
   wait(750, msec);
   //STOP ARMS
   MotorGroup1.setVelocity(0, percent);
   MotorGroup1.setStopping(hold);
   wait(1200, msec);//after forward now turn
   FR.spin(reverse, 100, pct);
   FL.spin(forward, 100, pct);
   BR.spin(reverse, 100, pct);
   BL.spin(forward, 100, pct);

//after pivot
   wait(225, msec);//[pivot time]
   FR.spin(forward, 100, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 100, pct);
   BL.spin(forward, 100, pct);
   
   wait(1100, msec);
   FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);

   //pPICK UP

  
  wait(50, msec);
   Tread.spin(forward, 100, pct);
   MotorGroup1.spin(forward, 40, pct);
  wait(500, msec);
   //trick
  MotorGroup1.spin(reverse, 40, pct);
   wait(100, msec);
   MotorGroup1.spin(forward, 40, pct);
   wait(100, msec);
  MotorGroup1.setVelocity(0, percent);
    MotorGroup1.setStopping(hold);
   FR.spin(reverse, 80, pct);
   FL.spin(reverse, 80, pct);
   BR.spin(reverse, 80, pct);
    BL.spin(reverse, 80, pct);
    wait(900, msec);//time DCT pivot
FR.spin(forward, 100, pct);
   FL.spin(reverse, 100, pct);
   BR.spin(forward, 100, pct);
   BL.spin(reverse, 100, pct);
   wait(300, msec);//[pivot time]
   Tread.setVelocity(0, pct);
  FR.spin(reverse, 100, pct);
   FL.spin(reverse, 100, pct);
   BR.spin(reverse, 100, pct);
    BL.spin(reverse, 100, pct);
    wait(1750, msec);
    FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);
   
}

void drive(){
  FR.spin(forward, Controller1.Axis2.position(pct), pct);
  FL.spin(forward, Controller1.Axis3.position(pct), pct);
  BR.spin(forward, Controller1.Axis2.position(pct), pct);
  BL.spin(forward, Controller1.Axis3.position(pct), pct);
  if(Controller1.Axis3.position(pct) == 0){
    BL.setStopping(hold);
  }
  if(Controller1.Axis2.position(pct) == 0){
    BR.setStopping(hold);
  }
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

bool flickThing(){
  if(on == false){
    return true;
  }
  else{
    return false;
  }
}

//bool flickThing2(){
//  if(off == false){
//    return true;
//  }
//  else{
//    return false;
//  }
//}

void flick(){
  if(Controller1.ButtonA.pressing()){
    waitUntil(!Controller1.ButtonA.pressing());
    DigitalOutA.set(flickThing());
    DigitalOutB.set(flickThing());
    if(on == false){
      on = true;
      //off = true;
      }
    else{
      on = false;
      //off = false;
      }
  }
}

int boosterSpeed(){
  if(Controller1.ButtonR1.pressing()){
    return -100;
  }
  else if(Controller1.ButtonR2.pressing()){
    return 100;
  }
  else{
    return 0;
  }
}

void booster(){
  DriveBooster.spin(fwd, boosterSpeed(), pct);
}

void userControl(){
  vexcodeInit();
  //INITIAL ACTUATOR COMNMANDS
  MotorGroup1.setStopping(hold);
  DigitalOutA.set(true);
  DigitalOutB.set(true);
  while(true){
  drive();
  booster();
  tread();
  lift();
  flick();
  }
}

int main(){
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);
  DigitalOutA.set(true);
  DigitalOutB.set(true);
  while (true) {
    wait(100, msec);
  }
}
