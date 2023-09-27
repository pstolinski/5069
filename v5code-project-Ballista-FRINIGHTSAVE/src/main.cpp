/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\vexrobotics                                      */
/*    Created:      Mon Nov 28 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Rotation             rotation      5               
// Winch                motor         14              
// Button               limit         D               
// FL                   motor         11              
// BL                   motor         12              
// FR                   motor         17              
// BR                   motor         18              
// GPS                  gps           7               
// Winch2               motor         20              
// Expander21           triport       21              
// Tracking             encoder       C, D            
// Expansion1           led           E               
// Expansion2           led           F               
// Expansion3           led           G               
// Expansion4           led           H               
// LeftB                optical       1               
// Intake               motor_group   13, 16          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <cmath>

using namespace vex;

competition Competition;

std::string Team = "Blue";
float Scope = 1;

int Marker1 = 0;
int MarkerHandler()
{
  if (Team == "Red")
  {
    int Mx = 1350;
    int My = 1350;
    while (true)
    {
      if (Mx > GPS.xPosition(mm) && My > GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (Mx - GPS.xPosition(mm)) / (My - GPS.yPosition(mm)) )* 180 / M_PI);
      }
      if (Mx > GPS.xPosition(mm) && My < GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (Mx - GPS.xPosition(mm)) / (GPS.yPosition(mm) - My) )* 180 / M_PI);
      }
      if (Mx < GPS.xPosition(mm) && My < GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (GPS.yPosition(mm) - My) / (GPS.xPosition(mm) - Mx) )* 180 / M_PI);
      }
      if (Mx < GPS.xPosition(mm) && My > GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (Mx - GPS.xPosition(mm)) / (My - GPS.yPosition(mm)) )* 180 / M_PI);
      }
    }
  }
  if (Team == "Blue")
  {
    int Mx = -1350;
    int My = -1350;
    while (true)
    {
      if (Mx > GPS.xPosition(mm) && My > GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (Mx - GPS.xPosition(mm)) / (My - GPS.yPosition(mm)) )* 180 / M_PI);
      }
      if (Mx > GPS.xPosition(mm) && My < GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (Mx - GPS.xPosition(mm)) / (GPS.yPosition(mm) - My) )* 180 / M_PI);
      }
      if (Mx < GPS.xPosition(mm) && My < GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (GPS.yPosition(mm) - My) / (GPS.xPosition(mm) - Mx) )* 180 / M_PI);
      }
      if (Mx < GPS.xPosition(mm) && My > GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (Mx - GPS.xPosition(mm)) / (My - GPS.yPosition(mm)) )* 180 / M_PI);
      }
    }
  }
  return 0;
}

int CA2 = 0;
int Angle2()
{
  while (true)
  {
    if (GPS.heading() > 180)
    {
      int AwayFromM = GPS.heading() - 180;
      CA2 = 0 - (180-(GPS.heading() - AwayFromM));
    }
  }
  return 0;
}

float Assist = 1;
float SpeedCap = 0.4;
int Aim()
{
  while (true)
  {
    if (Controller1.ButtonL2.pressing())
    {
      int Min = Marker1 - 50;
      if (Min < 0)
      {
        Min = 360 + Min;
      }
      int Max = Marker1 + 50;
      if (Max > 360)
      {
        Max = Max - 360;
      }
      if (GPS.heading() > Min && GPS.heading() < Max)
      {
        int ADist = abs(CA2 - Marker1);
        Scope = 1;
        SpeedCap = 1;
        Assist = 0.02 * ADist;
      }
      else
      {
        SpeedCap = 0.4;
        Assist = 1;
        Scope = 0.3;
      }
    }
    else
    {
      SpeedCap = 0.4;
      Assist = 1;
      Scope = 1;
    }
  }
  return 0;
}

float XAway = 0;
float YAway = 0;
void PointAway(int Dist, bool Back)
{
  int Angle = GPS.heading();
  int Q = 1;
  if (!Back)
  {
    if (Angle > 270)
    {
    Angle = Angle - 270;
    Q = 4;
    }
    else if (Angle > 180)
    {
      Angle = Angle - 180;
      Q = 3;
    }
    else if (Angle > 90)
    {
      Angle = Angle - 90;
      Q = 2;
    }
    int x = GPS.xPosition(mm);
    int y = GPS.yPosition(mm);
    float O = sin(Angle)*Dist;
    float A = cos(Angle)*Dist;
    if (Q == 1)
    {
      XAway = x + O;
      YAway = y + A;
    }
    else if (Q == 2)
    {
      XAway = x + A;
      YAway = y - O;
    }
    else if (Q == 3)
    {
      XAway = x - O;
      YAway = y - A;
    }
    else if (Q == 4)
    {
      XAway = x - A;
      YAway = y + O;
    }
  }
}

int Expand = 1;
int ExpansionSafty()
{
  Expansion1.on();
  Expansion2.on();
  Expansion3.on();
  Expansion4.on();
  while (true)
  {
    if (Controller1.ButtonUp.pressing() && Controller1.ButtonLeft.pressing())
    {
      waitUntil(!Controller1.ButtonUp.pressing());
      Controller1.Screen.print("tested");
      PointAway(108, true);
      if (XAway > 1829 || XAway < -1829)
      {
        Controller1.rumble(rumbleShort);
      }
      else if (YAway > 1829 || YAway < -1829)
      {
        Controller1.rumble(rumbleShort);
      }
      else
      {
        if (Expand == 4)
        {
          Expansion4.off();
          Expand++;
        }
        if (Expand == 3)
        {
          Expansion3.off();
          Expand++;
        }
        if (Expand == 2)
        {
          Expansion2.off();
          Expand++;
        }
        if (Expand == 1)
        {
          Expansion1.off();
          Expand++;
        }
      }
    }
    
  }
  return 0;
}

int SecondAmendment()
{
  Winch.setStopping(hold);
  Winch2.setStopping(hold);
  Winch.setPosition(0, degrees);
  Winch2.setPosition(0, degrees);
  Rotation.resetPosition();
  Winch.setVelocity(200, rpm);
  Winch2.setVelocity(200, rpm);
  Winch.spin(forward);
  Winch2.spin(forward);
  waitUntil(Button.pressing());
  Winch.stop();
  Winch2.stop();
  while (true)
  {
    waitUntil(Controller1.ButtonR2.pressing());
    waitUntil(!Controller1.ButtonR2.pressing());
    Winch.setVelocity(100, rpm);
    Winch2.setVelocity(100, rpm);
    Winch.spin(reverse);
    Winch2.spin(reverse);
    Brain.Timer.reset();
    waitUntil(!Button.pressing() || Brain.Timer.value() > 0.6);
    Winch.stop();
    Winch2.stop();
    Winch.setPosition(0,degrees);
    Winch2.setPosition(0,degrees);
    Rotation.resetPosition();
    Winch.setVelocity(200, rpm);
    Winch2.setVelocity(200, rpm);
    Winch.spin(forward);
    Winch2.spin(forward);
    waitUntil(Button.pressing());
    Winch.stop();
    Winch2.stop();
    Controller1.rumble(rumbleShort);
  }
  return 0;
}

float BSpeed = .75;
int TrainDrive()
{
  FL.spin(forward);
  BL.spin(forward);
  FR.spin(forward);
  BR.spin(forward);
  while (true)
  {
    int LeftPower = (Controller1.Axis3.position(percent) + (Controller1.Axis1.position(percent)*Assist)*SpeedCap)*Scope;
    int RightPower = (((Controller1.Axis1.position(percent)*Assist)*SpeedCap) - Controller1.Axis3.position(percent))*Scope;

    if (LeftPower < 0)
    {
      LeftPower = LeftPower*BSpeed;
    }
    if (RightPower < 0)
    {
      RightPower = RightPower*BSpeed;
    }

    FL.setVelocity(LeftPower * 2, rpm);
    BL.setVelocity(LeftPower * 2, rpm);
    FR.setVelocity(RightPower * 2, rpm);
    BR.setVelocity(RightPower * 2, rpm);
  }
  return 0;
}

int VibratorSystem()
{
  while (true)
  {

  }
  return 0;
}

int NoKneecaps()
{
  while (true)
  {
    if (Controller1.ButtonL1.pressing())
    {
      
    }
  }
  return 0; 
}

int Rev()
{
  Intake.setVelocity(200, rpm);
  while (true)
  {
    if (Controller1.ButtonRight.pressing())
    {
      Intake.setVelocity(-200, rpm);
      waitUntil(!Controller1.ButtonRight.pressing());
    }
    else
    {
      Intake.setVelocity(200, rpm);
      waitUntil(Controller1.ButtonRight.pressing());
    }
  }
  return 0;
}

int Suck()
{
  Intake.stop();
  while (true)
  {
    waitUntil(Controller1.ButtonA.pressing());
    waitUntil(!Controller1.ButtonA.pressing());
    Intake.spin(forward);
    waitUntil(Controller1.ButtonA.pressing());
    waitUntil(!Controller1.ButtonA.pressing());
    Intake.stop();
  }
  return 0;
}

/**
int Roll()
{
  Roller.setVelocity(100, pct);
  while (true)
  {
    if (Controller1.ButtonL1.pressing())
    {
      Roller.spin(forward);
      waitUntil(!Controller1.ButtonL2.pressing());
      Roller.stop();
    }
    if (Controller1.ButtonR1.pressing())
    {
      Roller.spin(reverse);
      waitUntil(!Controller1.ButtonL2.pressing());
      Roller.stop();
    }
  }
}

int LAutoRoll()
{
  while (true)
  {
    if (LeftB.isNearObject())
    {
      if (Team == "Blue")
      {
        if (LeftB.color() == red)
        {
          Roller.setVelocity(100, rpm);
          Roller.spin(reverse);
          waitUntil(LeftB.color() != red);
          Roller.stop();
        }
      }
      if (Team == "Red")
      {
        if (LeftB.color() == blue)
        {
          Roller.setVelocity(100, rpm);
          Roller.spin(reverse);
          waitUntil(LeftB.color() != blue);
          Roller.stop();
        }
      }
    }
  }
  return 0;
}

int RAutoRoll()
{
  while (true)
  {
    if (RightB.isNearObject())
    {
      if (Team == "Blue")
      {
        if (RightB.color() == red)
        {
          Roller.setVelocity(100, rpm);
          Roller.spin(reverse);
          waitUntil(RightB.color() != red);
          Roller.stop();
        }
      }
      if (Team == "Red")
      {
        if (RightB.color() == blue)
        {
          Roller.setVelocity(100, rpm);
          Roller.spin(reverse);
          waitUntil(RightB.color() != blue);
          Roller.stop();
        }
      }
    }
  }
  return 0;
}**/

void usercontrol(void)
{
  task a(MarkerHandler);
  task b(Angle2);
  task c(Aim);

  task e(SecondAmendment);
  task f(TrainDrive);
  task g(Rev);
  task h(Suck);
  //task i(Roll);

  //task l(LAutoRoll);
  //task r(RAutoRoll);
  
  task k(ExpansionSafty);
  while(true)
  {
    wait(230, sec);
  }
}

int Marker = 0;

void GetDirection(int Mx, int My)
{
while (true)
  {
    if (Mx > GPS.xPosition(mm) && My > GPS.yPosition(mm))
    {
      Marker = std::abs(atan( (Mx - GPS.xPosition(mm)) / (My - GPS.yPosition(mm)) )* 180 / M_PI);
    }
    if (Mx > GPS.xPosition(mm) && My < GPS.yPosition(mm))
    {
      Marker = std::abs(atan( (Mx - GPS.xPosition(mm)) / (GPS.yPosition(mm) - My) )* 180 / M_PI);
    }
    if (Mx < GPS.xPosition(mm) && My < GPS.yPosition(mm))
    {
      Marker = std::abs(atan( (GPS.yPosition(mm) - My) / (GPS.xPosition(mm) - Mx) )* 180 / M_PI);
    }
    if (Mx < GPS.xPosition(mm) && My > GPS.yPosition(mm))
    {
      Marker = std::abs(atan( (Mx - GPS.xPosition(mm)) / (My - GPS.yPosition(mm)) )* 180 / M_PI);
    }
  }
}



//Settings
float kP = 0.1;
float kD = 0.32;

void Fmove(int Distance, int offset)
{
  Distance = Distance - offset;
  Tracking.setPosition(0,degrees);
  int prevError = Distance - Tracking.position(degrees);
  while (true)
  {
    int error = Distance - Tracking.position(degrees); 
    int Dertive = error-prevError;
    prevError = error;
    int Power = (error*kP) + (Dertive*kD);
    FR.spin(forward, Power, voltageUnits::volt);
    BR.spin(forward, Power, voltageUnits::volt);
    FL.spin(forward, Power, voltageUnits::volt);
    BL.spin(forward, Power, voltageUnits::volt);
    wait(20, msec);
  }
}

void GoTo(int x, int y, int Speed)
{
  GetDirection(x,y);
  int GA = Marker;
  //if (GA-5 < 0)
  //{
    //GA = 360+(GA-5);
  //}

  if (GPS.heading() - Marker <= 180)
  {
    //Left
    FR.spin(forward, 100, rpm);
    BR.spin(forward, 100, rpm);
    FL.spin(reverse, 100, rpm);
    BL.spin(reverse, 100, rpm);
    waitUntil(GPS.heading() < Marker);
    FR.setStopping(hold);
    BR.setStopping(hold);
    FL.setStopping(hold);
    BL.setStopping(hold);
    FR.stop();
    BR.stop();
    FL.stop();
    BL.stop();
  }
  else
  {
    //Right
    FR.spin(reverse, 100, rpm);
    BR.spin(reverse, 100, rpm);
    FL.spin(forward, 100, rpm);
    BL.spin(forward, 100, rpm);
    waitUntil(GPS.heading() > GA && GPS.heading() < Marker);
    FR.setStopping(hold);
    BR.setStopping(hold);
    FL.setStopping(hold);
    BL.setStopping(hold);
    FR.stop();
    BR.stop();
    FL.stop();
    BL.stop();
  }
  Fmove(500, 0);
}

void moveForward(int d, int s){
  //bring back launcher to limit switch
  //Launch single preload
  //Bring back launcher to limit switch
  //launch second single preload
  //turn to angle (140deg) right
  //drive forward at rear roller
  //spin roller to apporpiate color


}

bool fire = false;
bool FireReady = false;
int auntonSecondAmendment(void)
{
  while (true)
  {
    waitUntil(fire);
    waitUntil(!fire);
    Winch.setVelocity(100, rpm);
    Winch2.setVelocity(100, rpm);
    Winch.spin(reverse);
    Winch2.spin(reverse);
    Brain.Timer.reset();
    waitUntil(!Button.pressing() /* || Brain.Timer.value() > 0.6 */);
    Winch.stop();
    Winch2.stop();
    Winch.setPosition(0,degrees);
    Winch2.setPosition(0,degrees);
    Rotation.resetPosition();
    Winch.setVelocity(200, rpm);
    Winch2.setVelocity(200, rpm);
    Winch.spin(forward);
    Winch2.spin(forward);
    waitUntil(Button.pressing());
    Winch.stop();
    Winch2.stop();
    Controller1.rumble(rumbleShort);
  }
  return 0;
}

void turnto(int Marker)
{
  int GA = Marker;
  if (GPS.heading() - Marker <= 180)
  {
    //Left
    FR.spin(forward, 100, rpm);
    BR.spin(forward, 100, rpm);
    FL.spin(reverse, 100, rpm);
    BL.spin(reverse, 100, rpm);
    waitUntil(GPS.heading() < Marker);
    FR.setStopping(hold);
    BR.setStopping(hold);
    FL.setStopping(hold);
    BL.setStopping(hold);
    FR.stop();
    BR.stop();
    FL.stop();
    BL.stop();
  }
  else
  {
    //Right
    FR.spin(reverse, 100, rpm);
    BR.spin(reverse, 100, rpm);
    FL.spin(forward, 100, rpm);
    BL.spin(forward, 100, rpm);
    waitUntil(GPS.heading() > GA && GPS.heading() < Marker);
    FR.setStopping(hold);
    BR.setStopping(hold);
    FL.setStopping(hold);
    BL.setStopping(hold);
    FR.stop();
    BR.stop();
    FL.stop();
    BL.stop();
  }
}

void MF(int amount, int speed)
{
  FL.setVelocity(speed, rpm);
  FR.setVelocity(speed, rpm);
  BL.setVelocity(speed, rpm);
  BR.setVelocity(speed, rpm);
  FL.spinFor(forward, amount, degrees, false);
  FR.spinFor(reverse, amount, degrees, false);
  BL.spinFor(forward, amount, degrees, false);
  BR.spinFor(reverse, amount, degrees, true);
  FL.stop();
  FR.stop();
  BL.stop();
  BR.stop();
}

void TF(int amount, int speed)
{
  FL.setVelocity(speed, rpm);
  FR.setVelocity(speed, rpm);
  BL.setVelocity(speed, rpm);
  BR.setVelocity(speed, rpm);
  FL.spinFor(forward, amount, degrees, false);
  FR.spinFor(forward, amount, degrees, false);
  BL.spinFor(forward, amount, degrees, false);
  BR.spinFor(forward, amount, degrees, true);
  FL.stop();
  FR.stop();
  BL.stop();
  BR.stop();
}
void autonomous(void)
{
  task aa(auntonSecondAmendment);
  //task l(LAutoRoll);
  //task r(RAutoRoll);
  //task a(Angle2);
  
  MF(50, 50);
  wait(.5, sec);
  fire = false;
  wait (1, msec);
  fire = true;

  wait(.5, sec);

  fire = false;
  wait (1, msec);
  fire = true;
  
  wait(5, sec);
  Intake.setVelocity(200, rpm);
  Intake.spin(forward);
  wait(2, sec);
  Intake.stop();
  fire = true;
  wait (1, msec);
  fire = false;
  wait(1, sec);
  
  TF(130, 50);
  MF(360, 50);
  TF(185, 50);
  MF(360, 50);

}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);
  
  if (Team == "Red")
  {
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(0,0, 480 ,240);
    Brain.Screen.setCursor(2,1);
    Brain.Screen.setFont(monoXXL);
    Brain.Screen.print("     5069X");
  }
  if (Team == "Blue")
  {
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(0,0, 480 ,240);
    Brain.Screen.setCursor(2,1);
    Brain.Screen.setFont(monoXXL);
    Brain.Screen.print("     5069X");
  }
  while (true) 
  {
   wait(240, seconds);
  }
}