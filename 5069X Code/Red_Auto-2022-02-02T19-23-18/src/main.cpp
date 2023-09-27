// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DigitalOutA          digital_out   A               
// FL                   motor         12              
// FR                   motor         11              
// BL                   motor         14              
// BR                   motor         13              
// VisionSensor         vision        21              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;
int centerFOV = 158;
int offsetX = 15;
int hw = 0;
int h = 0;
int w = 0;
int left_limit = 105; 
int right_limit = 210;

void red_move()
{
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
//Robot turns towards the red mobile goal

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




int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit()     ;
  red_move();
}





 