// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// VisionSensor         vision        21              
// FL                   motor         12              
// FR                   motor         11              
// BL                   motor         14              
// BR                   motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;
int centerFOV = 158;
int offsetX = 15;
int run = 0; // Will be used as a precaution before running forward code
void auto_turn()
{
   Brain.Screen.clearLine();
   while(true)
   {

if(VisionSensor.largestObject.centerX == centerFOV + offsetX || VisionSensor.largestObject.centerX == centerFOV - offsetX )//If the object is to the left then turns right
     {
         FL.setVelocity(0, pct);
     BL.setVelocity(0, pct);
     FR.setVelocity(0, pct);
    BL.setVelocity(0, pct);
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("doneturn");
       break;
     } 
   
   
   VisionSensor.takeSnapshot(VisionSensor__SIG_YELLOW);
   if(VisionSensor.largestObject.exists)
   {
     Brain.Screen.setCursor(1,1);
     Brain.Screen.print("found turning now");
     if(VisionSensor.largestObject.centerX > centerFOV + offsetX)//If the object is to the left then turns right
     {
       FL.spin(forward, 20, percent);
       FR.spin(reverse, 20, percent);
       BL.spin(forward, 20, percent); 
       BR.spin(reverse, 20, percent);
     }
   
   else if(VisionSensor.largestObject.centerX < centerFOV - offsetX) // If the object is to the right then turn left
   {
      FL.spin(reverse, 20, percent);
       FR.spin(forward, 20, percent);
       BL.spin(reverse, 20, percent); 
       BR.spin(forward, 20, percent);
     //Spin Motors
   }
   }
   }
   //Extra precaution for running the forward code
   
}

int hw = 0;
int h = 0;
int w = 0;
void movefwd()
{
  while(true){
  VisionSensor.takeSnapshot(VisionSensor__SIG_YELLOW);
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
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
   auto_turn();
    movefwd();
   
}
