/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\pstolinski                                       */
/*    Created:      Mon Nov 15 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FR                   motor         15              
// FL                   motor         17              
// BR                   motor         18              
// BL                   motor         13              
// DriveBooster         motor         19              
// Tread                motor         16              
// MotorGroup1          motor_group   14, 20          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;

int treadSpeedSet = 75;
int liftSpeedSet = 100;
int y = 0;
int x = 0;

void leftSideGo(){

}

void autonomous(){
  MotorGroup1.spin(reverse, 100, pct);
  wait(250, msec);
  FR.spin(forward, 100, pct);
  FL.spin(forward, 100, pct);
  BR.spin(forward, 100, pct);
  BL.spin(forward, 100, pct);
  wait(550, msec);
  MotorGroup1.setVelocity(0, percent);
  MotorGroup1.setStopping(hold);  
  //get the yellow
  wait(1000, msec);//additional straight boost time 
  FR.spin(reverse, 100, pct);
  BR.spin(reverse, 100, pct);
  wait(100, msec);//[turning time]
  FR.spin(forward, 100, pct);
  BR.spin(forward, 100, pct);
  wait(1000, msec);//[remaining forward time to the yellow goal]
  FR.stop();
  BR.stop();
  wait(1000, msec);
  
  FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);
  wait(0, msec);
  //LIFt IT
  
   MotorGroup1.spin(forward, 60, pct);
   
  wait(2000, msec);
   //trick
  MotorGroup1.setVelocity(0, percent);
  MotorGroup1.setStopping(hold);
   FR.spin(reverse, 70, pct);
   FL.spin(reverse, 100, pct);
   BR.spin(reverse, 70, pct);
    BL.spin(reverse, 100, pct);
    
    wait(1500, msec);//time to back up into home zone  
    Tread.spin(forward, 100, pct);
  wait(1000, msec);
 
MotorGroup1.setVelocity(0, percent);
  MotorGroup1.setStopping(hold);
    wait(300, msec);
    FR.spin(reverse, 0, pct);
   FL.spin(reverse, 0, pct);
   BR.spin(reverse, 0, pct);
    BL.spin(reverse, 0, pct);
  wait(4000, msec);
   Tread.setVelocity(0, percent);
   

  
   
}

int boosterSpeed(){
  if(Controller1.ButtonR1.pressing()){
    return -150;
  }
  else if(Controller1.ButtonR2.pressing()){
    return 150;
  }
  else{
    return 0;
    DriveBooster.setStopping(hold);
  }
}

void drive(){
  if(Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing()){
  FR.setVelocity(0, pct);
  FL.setVelocity(0, pct);  
  FR.setStopping(coast);
  FL.setStopping(coast);
  BR.spin(forward, Controller1.Axis2.position(pct), pct);
  BL.spin(forward, Controller1.Axis3.position(pct), pct);
  DriveBooster.spin(fwd, boosterSpeed(), pct);
  }else{
    FR.spin(forward, (Controller1.Axis2.position(pct)), pct);
    FL.spin(forward, (Controller1.Axis3.position(pct)), pct);
    BR.spin(forward, (Controller1.Axis2.position(pct)), pct);
    BL.spin(forward, (Controller1.Axis3.position(pct)), pct);
    DriveBooster.spin(fwd, boosterSpeed(), pct);
    DriveBooster.setStopping(hold);
  }
}

int treadSpeed(){
  if(Controller1.ButtonDown.pressing()){
    return (treadSpeedSet * -1);
  }
  else if(Controller1.ButtonUp.pressing()){
    return treadSpeedSet;
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
    return liftSpeedSet;
  }
  else if(Controller1.ButtonL2.pressing()){
    return (liftSpeedSet * -1);
  }
  else{
    return 0;
  }
}

void lift(){
  MotorGroup1.spin(forward, liftSpeed(), pct);
}


void userControl(){
  vexcodeInit();
  MotorGroup1.setStopping(hold);
  while(true){
  drive();
  tread();
  lift();
  //flick();
  }
}

int main(){
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);
  while (true) {
    wait(10, msec);
  }
}