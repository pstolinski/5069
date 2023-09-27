/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Rodri                                            */
/*    Created:      Wed Mar 15 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// L1                   motor         14              
// L2                   motor         15              
// R1                   motor         18              
// R2                   motor         12              
// Winch                motor         17              
// WDist                distance      3               
// Intake               motor         10              
// L3                   motor         16              
// R3                   motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <cmath>
 
using namespace vex;

competition Competition;

std::string Team = "Blue";
std::string Auton = "Right";  

int PS = 0;
int PY = 0;
void ScreenGoTo(int x, int y)
{
  PS = 240 + x;
  PY = 240 - (y + 120);
}

int cs()
{
  while (true)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("Nm: %.8f", Winch.torque(Nm));
    Brain.Screen.newLine();
    Brain.Screen.print("Current: %.8f", Winch.current());
    Brain.Screen.newLine();
    Brain.Screen.print("inch-pounds: %.8f", Winch.torque(InLb));
    Brain.Screen.newLine();
    Brain.Screen.print("Efficiency: ");
    Brain.Screen.print(Winch.efficiency(percent));
    Brain.Screen.print("%");
    Brain.Screen.newLine();
    Brain.Screen.print("Reel: ");
    Brain.Screen.print(WDist.objectDistance(mm)); //Distance to distance sensor
    Brain.Screen.print("mm");
    wait(0.05, sec);
  }
  return 0;
}

int Reel()
{
  while (true)
  {

    Winch.spin(reverse, 200, rpm);
    waitUntil(WDist.objectDistance(inches) < 1.6);//is this the armed distance
    Winch.stop(hold);
    waitUntil(!Controller1.ButtonR2.pressing());
    waitUntil(Controller1.ButtonR2.pressing());
    Winch.spin(forward, 200, rpm);
    waitUntil(WDist.objectDistance(inches) > 6.6);
  }
  return 0;
}

float Scope = 1;
int Aim()
{
  while (true)
  {
    if (Controller1.ButtonR1.pressing())
    {
      Scope = 0.5; //How much aiming lowers your turn speed, treat as persentage 1 being 100% and 0.5 being 50%, This changes your speed after your joystick and speed equlizer is calculeted so that means in easy terms Speed = (Joystick position * Turn Speed) * Scope
    }
    else
    {
      Scope = 1; //KEEP THIS AS 1
    }
  }
  return 0;
}

float TSpeed = 0.65; //treat as percentage .50 = 50% .65 = 65% 1 = 100%
int TrainDrive()
{
  while (true)
  {
    L1.stop(hold);
    L2.stop(hold);
    L3.stop(hold);
    R1.stop(hold);
    R2.stop(hold);
    R3.stop(hold);
    waitUntil(Controller1.Axis3.position(percent) != 0 || Controller1.Axis1.position(percent) != 0);
    L1.spin(forward);
    L2.spin(forward);
    L3.spin(forward);
    R1.spin(forward);
    R2.spin(forward);
    R3.spin(forward);
    while (Controller1.Axis3.position(percent) != 0 || Controller1.Axis1.position(percent) != 0)
    {
      int LeftPower = (Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent)*TSpeed)*Scope;
      int RightPower = (Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent)*TSpeed)*Scope;
      L1.setVelocity(LeftPower*6, rpm);
      L2.setVelocity(LeftPower*6, rpm);
      L3.setVelocity(LeftPower*6, rpm);
      R1.setVelocity(RightPower*6, rpm);
      R2.setVelocity(RightPower*6, rpm);
      R3.setVelocity(RightPower*6, rpm);
      wait(20, msec);
    }
  }
  return 0;
}

int Suck()
{
  while (true)
  {
    Intake.stop(hold);
    waitUntil(!Controller1.ButtonL2.pressing());
    waitUntil(Controller1.ButtonL2.pressing());
    Intake.spin(reverse, 600, rpm);
    waitUntil(!Controller1.ButtonL2.pressing());
    waitUntil(Controller1.ButtonL2.pressing());
  }
  return 0;
}

int Rev()
{
  while (true)
  {
    waitUntil(Controller1.ButtonL1.pressing());
    task::stop(Suck);
    Intake.spin(forward, 600, rpm);
    waitUntil(!Controller1.ButtonL1.pressing());
    Intake.stop(hold);
    task a(Suck);
  }
  return 0;
}

int sw()
{
  task a1(Rev);
  task a(Suck);
  task a2(Reel);
  while (true)
  {
    task b(TrainDrive);
    waitUntil(Brain.Screen.pressing());
    waitUntil(!Brain.Screen.pressing());
    L1.stop(coast);
    L2.stop(coast);
    L3.stop(coast);
    R1.stop(coast);
    R2.stop(coast);
    R3.stop(coast);
    task::stop(TrainDrive);
    waitUntil(Brain.Screen.pressing());
    waitUntil(!Brain.Screen.pressing());
  }
  return 0;
}

void usercontrol()
{
  task a(cs);
  task a1(Rev);
  task a2(Suck);
  task a3(Reel);
  task a4(Aim);
  task a5(TrainDrive);
}

void auton()
{
  
}

int main() 
{
  //task qwe(holder);
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //Inertial.calibrate();
  //wait(3, sec);
  //Controller1.rumble(rumblePulse);
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(auton);
  
  while (true) 
  {
    wait(20, msec);    
  }
}
