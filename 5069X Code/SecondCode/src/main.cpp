/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Thanish Kashyap, Patrick Stolinski                        */
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
// DigitalOutB          digital_out   B               
// DigitalOutA          digital_out   A               
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
  //FORWARD AND LOWER ARMS
   FR.spin(forward, 100, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 100, pct);
   BL.spin(forward, 100, pct);
   MotorGroup1.spin(reverse, 100, pct);
   wait(750, msec);
   //STOP ARMS
   MotorGroup1.setVelocity(0, percent);
   MotorGroup1.setStopping(hold);
  wait(2000, msec);
   FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);
   //STOP EVERYTHING AND LOWER THE ARM-- 
  //MAY NEED TO BE SWITCHED -- STRICTLY A GUESS
   wait(100, msec);//WITHOUT DELAY & WITH THE GOAL ATTACHED MOVE BACK
   MotorGroup1.spin(forward, 40, pct);
   Tread.spin(forward, 100, pct);
   wait(750, msec);

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
    wait(2300, msec);
    

   Tread.setVelocity(0, pct);
   FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);
   
   wait(250, msec);
   MotorGroup1.spin(reverse, 50, pct);
   FR.spin(reverse, 70, pct);
   FL.spin(reverse, 70, pct);
   BR.spin(reverse, 70, pct);
   BL.spin(reverse, 70, pct);
   wait(1000, msec);
   FR.spin(reverse, 40, pct);
   FL.spin(forward, 40, pct);
   BR.spin(reverse, 40, pct);
   BL.spin(forward, 40, pct);
   wait(500, msec);//CHARGE AT BLUE GOAL
   FR.spin(forward, 100, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 100, pct);
   BL.spin(forward, 100, pct);
   wait(1500, msec);//STOP EVERYTHING, LIFT THE GOAL UP SINCE ITS IN FORKLIFT 
   //AS IT IS RAISED START THE TREAD PULLING
  MotorGroup1.setVelocity(0, percent);
   MotorGroup1.setStopping(hold);
   wait(200, msec);
   FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);
   wait(200, msec);
   
  MotorGroup1.spin(forward, 50, pct);  
   Tread.spin(forward, 100, pct);
   wait(200, msec);
   FR.spin(reverse, 80, pct);
   FL.spin(reverse, 80, pct);
   BR.spin(reverse, 80, pct);
   BL.spin(reverse, 80, pct);
   wait(500, msec);
  FR.setVelocity(0, percent);
   FL.setVelocity(0, percent);
   BR.setVelocity(0, percent);
   BL.setVelocity(0, percent);
   FR.setStopping(brake);
   FL.setStopping(brake);
   BR.setStopping(brake);
   BL.setStopping(brake);
   wait(0, msec);
   MotorGroup1.setVelocity(0, percent);
   MotorGroup1.setStopping(hold); 
   wait(150, msec);
   MotorGroup1.spin(reverse, 40, pct);
   wait(150, msec);
   MotorGroup1.spin(forward, 40, pct);
   wait(150, msec);
   MotorGroup1.setVelocity(0, percent);
   MotorGroup1.setStopping(hold); 
   wait(1000, msec);//MOVE BACK ENOUGH TO GET GOAL PAST HOME LINE
   Tread.setVelocity(0, pct);




   MotorGroup1.setStopping(hold);//TURN TOWARDS YELLOW GOAL FOR PICK UP DURING DRIVER
   FR.spin(reverse, 100, pct);
   FL.spin(reverse, 100, pct);
   BR.spin(reverse, 100, pct);
   BL.spin(reverse, 25, pct);
   wait(750, msec);//STOP EVERYTHING
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

void userControl(){
  vexcodeInit();
  //INITIAL ACTUATOR COMNMANDS
  MotorGroup1.setStopping(hold);
  DigitalOutA.set(true);
  DigitalOutB.set(true);
  while(true){
  drive();
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
