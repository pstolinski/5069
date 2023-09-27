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
// VisionSensor         vision        11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;

int treadSpeedSet = 75;
int liftSpeedSet = 50;
int y = 0;
int x = 0;

void autonomous(){
  //Robot scores donuts
  DigitalOutA.set(false);
wait(100, msec);
DigitalOutA.set(true);
//-------------------------------------------------------------------------------
//Robot moves forward
FL.spin(fwd, 100, percent);
    BL.spin(fwd, 100, percent);
    FR.spin(fwd, 100, percent);
    BR.spin(fwd, 100, percent);
    wait(1000, msec);
//-------------------------------------------------------------------------------
//Robot turns towards the red mobile goal -- I THINK HE MEANT YELLOW

while(true)
{
if(VisionSensor.largestObject.centerX == centerFOV + offsetX || VisionSensor.largestObject.centerX == centerFOV - offsetX )//If the object is at center then stops the while loop 
     {
         FL.setVelocity(0, pct);
     BL.setVelocity(0, pct);
     FR.setVelocity(0, pct);
    BL.setVelocity(0, pct);
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("doneturn");
       break;
     } 
   VisionSensor.takeSnapshot(VisionSensor__SIG_RED);
   //If it doesnt see the color red then spins until it does
   while(true)
   {
   if(!(VisionSensor.largestObject.exists))
   {
     FL.spin(fwd, 100, percent);
    BL.spin(fwd, 100, percent);
    FR.spin(reverse, 100, percent);
    BR.spin(reverse, 100, percent);   
    VisionSensor.takeSnapshot(VisionSensor__SIG_RED);
   }
   else
   {
     break;//Now it sees object
   }
   }
   if(VisionSensor.largestObject.exists)
   {
     Brain.Screen.setCursor(1,1);
     Brain.Screen.print("found turning now");
     while(true)//You know that the largest object of the color of choice exists so now you can turn until the object is in the center
     {
     if(VisionSensor.largestObject.centerX > left_limit && VisionSensor.largestObject.centerX < right_limit)
     {
     if(VisionSensor.largestObject.centerX > centerFOV + offsetX)//If the object is to the left then turns right
     {
       FL.spin(forward, 100, percent);
       FR.spin(reverse, 100, percent);
       BL.spin(forward, 100, percent); 
       BR.spin(reverse, 100, percent);
     }
   
   else if(VisionSensor.largestObject.centerX < centerFOV - offsetX) // If the object is to the right then turn left
   {
      FL.spin(reverse, 100, percent);
       FR.spin(forward, 100, percent);
       BL.spin(reverse, 100, percent); 
       BR.spin(forward, 100, percent);
     
   }
   }
   else
   {
    VisionSensor.takeSnapshot(VisionSensor__SIG_RED);
   }
     }
     
   }
}
   //--------------------------------------------------------------------------------------------------------------------------------
   //Robot moves towards red mobile goal
   while(true){
  VisionSensor.takeSnapshot(VisionSensor__SIG_RED);
  h = VisionSensor.objects[0].height;
  w = VisionSensor.objects[0].width;
  hw = h*w; 
  if (hw > 20000)
  {
    FL.stop();
    BL.stop();
    BR.stop();
    FR.stop();
    break;
  }
  else if(hw < 53172)// It is less than bc height and width gets bigger as you get closer so once you are close enough you can stop
  {   
    Brain.Screen.clearScreen();
   Brain.Screen.setCursor(1,1);
    Brain.Screen.print("FORWARD!!!");
    FL.spin(forward, 100, percent);
    FR.spin(forward, 70, percent);
    BL.spin(forward, 100, percent); 
    BR.spin(forward, 70, percent);
  }
  else
  {
    Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("I THINK IM THERE!");
      FL.setVelocity(0, pct);
     BL.setVelocity(0, pct);
     FR.setVelocity(0, pct);
    BL.setVelocity(0, pct);
    break;
  }

   }
   //----------------------------------------------------------------------------------------------------------------------------------------

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