/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\vexrobotics                                      */
/*    Created:      Thu Dec 09 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FR                   motor         1               
// FL                   motor         2               
// BR                   motor         3               
// BL                   motor         4               
// MotorGroup1          motor_group   5, 6            
// Tread                motor         7               
// DigitalOutB          digital_out   B               
// DigitalOutC          digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;

int tradSpeed = 100;
int lifSpeed = 25;
int y = 0;
int x = 0;
bool pneuOn = false;

void autonomous(){
  //FORWARD AND LOWER ARMS
   FR.spin(forward, 100, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 100, pct);
   BL.spin(forward, 100, pct);
   MotorGroup1.spin(forward, 100, pct);
   wait(250, msec);
   //STOP ARMS
   MotorGroup1.setVelocity(0, percent);
   MotorGroup1.setStopping(hold);
   wait(250, msec);
   //START BANK TO STOP TO THE --RIGHT-- OF THE YELLOW MOBILE GOAL
   FR.spin(forward, 80, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 80, pct);
   BL.spin(forward, 100, pct);
   wait(1200, msec);//MAY NEED TO BE SHORTENED BASED ON LENGTH TO SIDE OF GOAL
   FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);
   //STOP EVERYTHING AND LOWER THE ARM-- 
   DigitalOutB.set(true); //MAY NEED TO BE SWITCHED -- STRICTLY A GUESS
   wait(0, msec);//WITHOUT DELAY & WITH THE GOAL ATTACHED MOVE BACK
   FR.spin(reverse, 100, pct);
   FL.spin(reverse, 100, pct);
   BR.spin(reverse, 100, pct);
   BL.spin(reverse, 100, pct);
   wait(4100, msec);//MOVE BACK ENOUGH TO GET GOAL PAST HOME LINE 
   DigitalOutB.set(false);//RELEASE GOAL
   //TURN RIGHT TO LINE UP WITH BLUE GOAL
   FR.spin(forward, 80, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 80, pct);
   BL.spin(forward, 100, pct);
   wait(350, msec);//CHARGE AT BLUE GOAL
   FR.spin(forward, 100, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 100, pct);
   BL.spin(forward, 100, pct);
   MotorGroup1.spin(forward, 25, pct);//does this need to be flipped? LOWER ARMS WHILE CHARGING
   wait(750, msec);//STOP EVERYTHING, LIFT THE GOAL UP SINCE ITS IN FORKLIFT 
   //AS IT IS RAISED START THE TREAD PULLING
   FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);
   MotorGroup1.spin(reverse, 25, pct);
   Tread.spin(forward, 100, pct);//need to be reversed?
   wait(300, msec);
   //BACK UP FOR GOAL TO PAST WIN POINT LINE -- SHOULD BE ON ROBOT
   FR.spin(reverse, 50, pct);
   FL.spin(reverse, 50, pct);
   BR.spin(reverse, 50, pct);
   BL.spin(reverse, 50, pct);
   wait(500, msec);
   MotorGroup1.setVelocity(0, percent);
   MotorGroup1.setStopping(hold);//TURN TOWARDS YELLOW GOAL FOR PICK UP DURING DRIVER
   FR.spin(reverse, 50, pct);
   FL.spin(reverse, 25, pct);
   BR.spin(reverse, 50, pct);
   BL.spin(reverse, 25, pct);
   wait(450, msec);//STOP EVERYTHING
   FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);
   Tread.setVelocity(0, percent);




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

void pneu(){
  if(Controller1.ButtonA.pressing()){
    if(pneuOn == false){
    DigitalOutB.set(true);
    DigitalOutC.set(true);
    pneuOn = true;
    }else if(pneuOn == true){
    DigitalOutB.set(false);
    DigitalOutC.set(false);
    pneuOn = false;
    }
    waitUntil(!Controller1.ButtonA.pressing());
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
  pneu();
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
