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

void autonomous(){
  //FORWARD AND LOWER ARMS
   FR.spin(forward, 100, pct);
   FL.spin(forward, 100, pct);
   BR.spin(forward, 100, pct);
   BL.spin(forward, 100, pct);
   MotorGroup1.spin(reverse, 100, pct);
   wait(425, msec);
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
   wait(800, msec);

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
   MotorGroup1.spin(reverse, 25, pct);
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