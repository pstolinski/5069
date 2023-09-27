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
// Button               limit         E               
// FL                   motor         11              
// BL                   motor         12              
// FR                   motor         17              
// BR                   motor         15              
// Intake               motor         13              
// GPS                  gps           7               
// Winch2               motor         20              
// Expander21           triport       21              
// Intake2              motor         16              
// Tracking             encoder       G, H            
// RightB               optical       9               
// LeftB                optical       2               
// Expansion1           led           A               
// Expansion2           led           B               
// Expansion3           led           C               
// Expansion4           led           D               
// Inertial             inertial      3               
// TInertial            inertial      4               
// Intake3              motor         18              
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <cmath>
 
using namespace vex;

competition Competition;

std::string Team = "Blue";
std::string Auton = "Right";

bool Lock = false;

//STATS
int Shots = 0;
int Rollers = 0;

int Min = 0;
int Max = 0;

float ADist = 0;
float RADist = 0;

float Factor = 0;

bool UseInertial = false;

float X = 0;
float Y = 0;
int Dir = 0;

int q = 0;

int OGDir = 0;
int Position()
{
  UseInertial = false;
  X = GPS.xPosition(mm);
  Y = GPS.yPosition(mm);
  Dir = GPS.heading();
  while (true)
  {
    if (false/*GPS.quality() < 90*/)
    {
      UseInertial = true;
      OGDir = GPS.heading();
      TInertial.setHeading(0,degrees);
      while (GPS.quality() < 90)
      {
        q = round(TInertial.heading(degrees));
        Dir = (OGDir + q)%360;
        float O = sin(Dir)*TInertial.acceleration(zaxis);
        float A = cos(Dir)*TInertial.acceleration(zaxis);
        float O2 = sin(Dir+90)*TInertial.acceleration(xaxis);
        float A2 = cos(Dir+90)*TInertial.acceleration(xaxis);
        X = X + (A + A2);
        Y = Y + (O + O2);
      }
    }
    else
    {
      UseInertial = false;
      X = GPS.xPosition(mm);
      Y = GPS.yPosition(mm);
      Dir = GPS.heading();
      if (GPS.quality() > 98)
      {
        OGDir = GPS.heading();
      }
    }
  }
  return 0;
}

float NegDist = 1;

int Marker1 = 0;
int MarkerHandler()
{
  if (Team == "Red")
  {
    int Mx = -1350;
    int My = -1350;
    //int Mx = 0;
    //int My = 0;
    while (true)
    {
      if (Mx > GPS.xPosition(mm) && My > GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (Mx - GPS.xPosition(mm)) / (My - GPS.yPosition(mm)) )* 180 / M_PI);
      }
      if (Mx > GPS.xPosition(mm) && My < GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (GPS.yPosition(mm) - My) / (Mx - GPS.xPosition(mm)) )* 180 / M_PI) + 90;
      }
      if (Mx < GPS.xPosition(mm) && My < GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (GPS.xPosition(mm) - Mx) / (GPS.yPosition(mm) - My) )* 180 / M_PI) + 180;
      }
      if (Mx < GPS.xPosition(mm) && My > GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (My - GPS.yPosition(mm)) / (Mx - GPS.xPosition(mm)) )* 180 / M_PI) + 270;
      }
      Min = Marker1 - 50;
      if (Min < 0)
      {
        Min = 360 + Min;
      }
      Max = Marker1 + 50;
      if (Max > 360)
      {
        Max = Max - 360;
      }
      NegDist = GPS.heading() - Marker1;
      ADist = std::abs(GPS.heading() - Marker1);
      if (ADist > 180)
      {
        RADist = 180 + (180 - ADist);
      }
      else
      {
        RADist = ADist;
      }
    }
  }
  if (Team == "Blue")
  {
    int Mx = 1350;
    int My = 1350;
    //int Mx = 0;
    //int My = 0;
    while (true)
    {
      if (Mx > GPS.xPosition(mm) && My > GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (Mx - GPS.xPosition(mm)) / (My - GPS.yPosition(mm)) )* 180 / M_PI);
      }
      if (Mx > GPS.xPosition(mm) && My < GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (GPS.yPosition(mm) - My) / (Mx - GPS.xPosition(mm)) )* 180 / M_PI) + 90;
      }
      if (Mx < GPS.xPosition(mm) && My < GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (GPS.xPosition(mm) - Mx) / (GPS.yPosition(mm) - My) )* 180 / M_PI) + 180;
      }
      if (Mx < GPS.xPosition(mm) && My > GPS.yPosition(mm))
      {
        Marker1 = std::abs(atan( (My - GPS.yPosition(mm)) / (Mx - GPS.xPosition(mm)) )* 180 / M_PI) + 270;
      }
      Min = Marker1 - 50;
      if (Min < 0)
      {
        Min = 360 + Min;
      }
      Max = Marker1 + 50;
      if (Max > 360)
      {
        Max = Max - 360;
      }
      NegDist = GPS.heading() - Marker1;
      ADist = std::abs(GPS.heading() - Marker1);
      if (ADist > 180)
      {
        RADist = 180 + (180 - ADist);
      }
      else
      {
        RADist = ADist;
      }
    }
  }
  return 0;
}

float XAway = 0;
float YAway = 0;
void PointAway(float x, float y, float Angle, int Dist)
{
  float O = cos(Angle * M_PI / 180)*Dist;
  float A = sin(Angle * M_PI / 180)*Dist;
  XAway = x + A;//x
  YAway = y + O;//y 
}

int Expand = 1;
bool AutonExpansion = false;
int ExpansionSafty()
{
  Expansion1.on();
  Expansion2.on();
  Expansion3.on();
  Expansion4.on();
  while (true)
  {
    if ((Controller1.ButtonUp.pressing() && Controller1.ButtonLeft.pressing()) || AutonExpansion)
    {
      waitUntil(!Controller1.ButtonUp.pressing() /*|| !AutonExpansion*/);
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("tested ");
      PointAway(X, Y, Dir, 2997);
      Brain.Screen.print(XAway);
      Brain.Screen.print(" ");
      Brain.Screen.print(YAway);
      if (XAway > 1803 || XAway < -1803 || YAway > 1803 || YAway < -1803)
      {
        Brain.Screen.print("WGoF");
      }
      else
      {
        if (Expand == 1)
        {
          Expansion4.off();
          Expansion1.off();
          wait(10, msec);
          Expansion3.off();
          Expansion2.off();
          Expand++;
        }
      }
    }
    
  }
  return 0;
}

bool AutonShoot = false;
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
  Lock = true;
  while (true)
  {
    waitUntil(Controller1.ButtonR2.pressing() || AutonShoot);
    waitUntil(!Controller1.ButtonR2.pressing() || !AutonShoot);
    Lock = false;
    Shots++;
    Winch.setVelocity(200, rpm);
    Winch2.setVelocity(200, rpm);
    Winch.spin(reverse);
    Winch2.spin(reverse);
    //Brain.Timer.reset();
    waitUntil(!Button.pressing() /*|| Brain.Timer.value() > 0.75*/);
    //wait(600, msec);
    Winch.spinFor(reverse, 265, degrees, false);
    Winch.spinFor(reverse, 265, degrees, true);
    Winch.stop();
    Winch2.stop();
    wait(50, msec);
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
    Lock = true;
    Controller1.rumble(rumbleShort);
  }
  return 0;
}
//
//
//
//
float Scope = 1;
int Aim()
{
  while (true)
  {
    if (Controller1.ButtonR1.pressing())
    {
      Scope = .1;
      waitUntil(!Controller1.ButtonR1.pressing());
    }
    else
    {
      Scope = 1;
      waitUntil(Controller1.ButtonR1.pressing());
    }
    wait(20, msec);
  }
  return 0;
}
//
//
//
//
float LeftPower = 0;
float RightPower = 0;
float BSpeed = .75;
int TrainDrive()
{
  //float Brakes = 2;

  FL.spin(forward);
  BL.spin(forward);
  FR.spin(forward);
  BR.spin(forward);
  FL.setStopping(coast);
  BL.setStopping(coast);
  FR.setStopping(coast);
  BR.setStopping(coast);
  while (true)
  {
    LeftPower = (Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent)*1.5) * Scope;
    RightPower = (Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent)*1.5) * Scope;

    FL.setVelocity(LeftPower * 2, rpm);
    BL.setVelocity(LeftPower * 2, rpm);
    FR.setVelocity(RightPower * -2, rpm);
    BR.setVelocity(RightPower * -2, rpm);
  }
  return 0;
}
//
//
//
//
int Screener()
{
  while (true)
  {
    /*
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("Shots Fired: ");
    Brain.Screen.print(Shots);
    Brain.Screen.newLine();
    Brain.Screen.print("Rollers: ");
    Brain.Screen.print(Rollers);
    Brain.Screen.newLine();
    */
    /*
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(GPS.xPosition(mm));
    Brain.Screen.print(" ");
    Brain.Screen.print(GPS.yPosition(mm));
    Brain.Screen.newLine();
    Brain.Screen.print(X);
    Brain.Screen.print(" ");
    Brain.Screen.print(Y);
    Brain.Screen.newLine();
    Brain.Screen.print("G Angle ");
    Brain.Screen.print(GPS.heading(degrees));
    Brain.Screen.newLine();
    Brain.Screen.print("Angle ");
    Brain.Screen.print(Dir);
    Brain.Screen.newLine();
    Brain.Screen.print("Q");
    Brain.Screen.print(q);
    Brain.Screen.newLine();
    Brain.Screen.print("OLD");
    Brain.Screen.print(OGDir);
    Brain.Screen.newLine();
    Brain.Screen.print("GPS Q");
    Brain.Screen.print(GPS.quality());
    */
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.newLine();

    Brain.Screen.newLine();
    Brain.Screen.print("Marker Angle ");
    Brain.Screen.print(Marker1);
    Brain.Screen.newLine();
    Brain.Screen.print("Distance to M Angle ");
    Brain.Screen.print(RADist);
    Brain.Screen.newLine();
    Brain.Screen.print("ADist ");
    Brain.Screen.print(ADist);
    Brain.Screen.newLine();
    Brain.Screen.print("Neg ");
    Brain.Screen.print(NegDist);
    Brain.Screen.newLine();
    Brain.Screen.print(LeftPower);
    Brain.Screen.newLine();
    Brain.Screen.print(RightPower);
    Brain.Screen.newLine();
    //
    wait(10, msec);
    /*
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Controller1.Screen.newLine();
    Controller1.Screen.print(RADist);
    wait(10, msec);
    */
  }
  return 0;
}
//
//
//
//
//
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

bool SuckOn = false;

int LAutoRoll()
{
  LeftB.setLightPower(20,percent);
  LeftB.setLight(ledState::on);
  while (true)
  {
    if (LeftB.isNearObject())
    {
      if (Team == "Blue")
      {
        if (LeftB.color() == red)
        {
          SuckOn = true;
          Intake.setVelocity(200, rpm);
          Intake2.setVelocity(200, rpm);
          Intake.spin(reverse);
          Intake2.spin(reverse); 
          waitUntil(LeftB.color() != red);
          wait(5, msec);
          Intake.stop();
          Intake2.stop();
          Controller1.rumble(rumblePulse);
          Rollers++;
          waitUntil(!LeftB.isNearObject());
          Intake.setVelocity(600, rpm);
          Intake2.setVelocity(600, rpm);
        }
      }
      if (Team == "Red")
      {
        if (LeftB.color() != red)
        {
          SuckOn = true;
          Intake.setVelocity(200, rpm);
          Intake2.setVelocity(200, rpm);
          Intake.spin(reverse);
          Intake2.spin(reverse);
          waitUntil(LeftB.color() == red);
          wait(5, msec);
          Intake.stop();
          Intake2.stop();
          Controller1.rumble(rumblePulse);
          Rollers++;
          waitUntil(!LeftB.isNearObject());
          Intake.setVelocity(600, rpm);
          Intake2.setVelocity(600, rpm);
        }
      }
    }
  }
  return 0;
}

int RAutoRoll()
{
  RightB.setLightPower(20,percent);
  RightB.setLight(ledState::on);
  while (true)
  {
    if (RightB.isNearObject())
    {
      if (Team == "Blue")
      {
        if (RightB.color() == red)
        {
          SuckOn = true;
          Intake.setVelocity(200, rpm);
          Intake2.setVelocity(200, rpm);
          Intake.spin(reverse);
          Intake2.spin(reverse);
          waitUntil(RightB.color() != red);
          wait(5, msec);
          Intake.stop();
          Intake2.stop();
          Controller1.rumble(rumblePulse);
          Rollers++;
          waitUntil(!LeftB.isNearObject());
          Intake.setVelocity(600, rpm);
          Intake2.setVelocity(600, rpm);
        }
      }
      if (Team == "Red")
      {
        if (RightB.color() != red)
        {
          SuckOn = true;
          Intake.setVelocity(200, rpm);
          Intake2.setVelocity(200, rpm);
          Intake.spin(reverse);
          Intake2.spin(reverse);
          waitUntil(RightB.color() == red);
          wait(5, msec);
          Intake.stop();
          Intake2.stop();
          Controller1.rumble(rumblePulse);
          Rollers++;
          waitUntil(!LeftB.isNearObject());
          Intake.setVelocity(600, rpm);
          Intake2.setVelocity(600, rpm);
        }
      }
    }
  }
  return 0;
}

bool AutonRev = false;
int Rev()
{
  Intake.setVelocity(600, rpm);
  Intake2.setVelocity(600, rpm);
  while (true)
  {
    if (LeftB.isNearObject() || RightB.isNearObject())
    {

    }
    else
    {
      if (Controller1.ButtonL1.pressing() || AutonRev)
      {
        Intake.spin(forward);
        Intake2.spin(forward);
        Intake3.spin(forward);
        Intake.setVelocity(-600, rpm);
        Intake2.setVelocity(-600, rpm);
        Intake3.setVelocity(-600, rpm);
        waitUntil(!Controller1.ButtonL1.pressing() || !AutonRev);
        if (!SuckOn)
        {
          Intake.stop(hold);
          Intake2.stop(hold);
        }
      }
      else
      {
        Intake.setVelocity(600, rpm); 
        Intake2.setVelocity(600, rpm);
        Intake3.setVelocity(600, rpm);
        waitUntil(Controller1.ButtonL1.pressing() || AutonRev);
      }
    }
  }
  return 0;
}

int Suck()
{
  Intake.stop(hold);
  Intake2.stop(hold);
  Intake3.stop(hold);
  SuckOn = false;
  while (true)
  {
    waitUntil(!Controller1.ButtonL2.pressing());
    waitUntil(Controller1.ButtonL2.pressing());
    if (SuckOn)
    {
      SuckOn = false;
      Intake.stop(hold);
      Intake2.stop(hold);
      Intake3.stop(hold);
    }
    else
    {
      SuckOn = true;
      Intake.spin(forward);
      Intake2.spin(forward);
      Intake3.spin(forward);
    }
    //Intake.stop(hold);
    //Intake2.stop(hold);
    //Intake3.stop(hold);
    //SuckOn = false;
    //waitUntil((!Controller1.ButtonL2.pressing()) /*&& (!RightB.isNearObject() || !LeftB.isNearObject())*/);
    //waitUntil((Controller1.ButtonL2.pressing()) /*&& (!RightB.isNearObject() || !LeftB.isNearObject())*/);
    //Intake.spin(forward);
    //Intake2.spin(forward);
    //Intake3.spin(forward);
    //SuckOn = true;
    //waitUntil((!Controller1.ButtonL2.pressing()) /*&& (!RightB.isNearObject() || !LeftB.isNearObject())*/);
    //waitUntil((Controller1.ButtonL2.pressing()) /*&& (!RightB.isNearObject() || !LeftB.isNearObject())*/);
  }
  return 0;
}
//
int VictorSuck()
{
  while (true)
  {
    if (Controller2.ButtonL1.pressing() || Controller2.ButtonL2.pressing())
    {
      task::stop(Rev);
      task::stop(Suck);
      Intake.spin(forward);
      Intake2.spin(forward);
      Intake3.spin(forward);
      while (Controller2.ButtonL1.pressing() || Controller2.ButtonL2.pressing())
      {
        if (Controller2.ButtonL1.pressing())
        {
          Intake.setVelocity(600, rpm);
          Intake2.setVelocity(600, rpm);
          Intake3.setVelocity(600, rpm);
        }
        else if (Controller2.ButtonL2.pressing())
        {
          Intake.setVelocity(-600, rpm);
          Intake2.setVelocity(-600, rpm);
          Intake3.setVelocity(-600, rpm);
        }
        vex::task::sleep(20);
      }
      AutonRev = false;
      task a(Rev);
      task b(Suck);
    }
    vex::task::sleep(20);
  }
  return 0;
}

int MAim()
{
  while (true)
  {
    if (Controller2.ButtonR1.pressing())
    {
      task::stop(TrainDrive);
      FL.spin(forward);
      BL.spin(forward);
      FR.spin(forward);
      BR.spin(forward);
      while (Controller2.ButtonR1.pressing() || RADist < 0.8)
      {
        int LeftPower = (Controller1.Axis1.position(percent)*1.5);
        int RightPower = (Controller1.Axis1.position(percent)*-1.5);
        if (Controller2.Axis1.position(percent) > 0)
        {
          if (Dir > Marker1 && Dir < Marker1 + 5)
          {
            LeftPower = 0;
            RightPower = 0;
            FL.stop(hold);
            BL.stop(hold);
            FR.stop(hold);
            BR.stop(hold);
          }
        }
        if (Controller2.Axis1.position(percent) < 0)
        {
          if (Dir < Marker1 && Dir > Marker1 - 5)
          {
            LeftPower = 0;
            RightPower = 0;
            FL.stop(hold);
            BL.stop(hold);
            FR.stop(hold);
            BR.stop(hold);
          }
        }
        FL.setVelocity(LeftPower * 2, rpm);
        BL.setVelocity(LeftPower * 2, rpm);
        FR.setVelocity(RightPower * -2, rpm);
        BR.setVelocity(RightPower * -2, rpm);
        vex::task::sleep(20);
      }
      task a(TrainDrive);
    }
    vex::task::sleep(20);
  }
  return 0;
}
//
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

////

//Settings
float LkP = 0.025209;
float LkD = 0.1492;

bool Arev = false;
int LDistance = 0;
int offset = 0;
int Lerror = 0;


bool FmoveReset = false;
int Fmove()
{
  //int ADistance = 0;
  Lerror = 0;
  int ADistance = LDistance - offset;
  Tracking.setPosition(0,degrees);
  int prevError = ADistance - Tracking.position(degrees)*-1;
  while (true)
  {
    if (FmoveReset)
    {
      FmoveReset = false;
      ADistance = 0;
      Lerror = 0;
      ADistance = LDistance - offset;
      Tracking.setPosition(0,degrees);
      prevError = ADistance - Tracking.position(degrees)*-1;
    }
    ADistance = LDistance - offset;
    if (Arev)
    {
      Lerror = ADistance - Tracking.position(degrees); 
    }
    else
    {
      Lerror = ADistance - Tracking.position(degrees)*-1; 
    }
    int Dertive = Lerror-prevError;
    int Power = (Lerror*LkP) + (Dertive*LkD);
    prevError = Lerror;
    if (Arev)
    {
      FR.spin(forward, Power, voltageUnits::volt);
      BR.spin(forward, Power, voltageUnits::volt);
      FL.spin(reverse, Power, voltageUnits::volt);
      BL.spin(reverse, Power, voltageUnits::volt);
      wait(20, msec);
    }
    else
    {
      FR.spin(reverse, Power, voltageUnits::volt);
      BR.spin(reverse, Power, voltageUnits::volt);
      FL.spin(forward, Power, voltageUnits::volt);
      BL.spin(forward, Power, voltageUnits::volt);
      wait(20, msec);
    }
  }
}

float TkP = 0.3;
float TkD = 1.0;

bool Aleft = false;
int TDistance = 0;
//int ADistance = 0;
//int error = 0;

bool FTurnReset = false;
int Terror = 0;

int FTurn()
{
  int ADistance = 0;
  ADistance = TDistance - offset;
  Inertial.setRotation(0, degrees);
  int prevError = ADistance - Inertial.rotation(degrees)*-1;
  while (true)
  {
    if (FTurnReset)
    {
      FTurnReset = false;
      ADistance = 0;
      Terror = 0;
      ADistance = TDistance - offset;
      Inertial.setRotation(0, degrees);
      prevError = ADistance - Inertial.rotation(degrees)*-1;
    }
    ADistance = TDistance - offset;
    if (Aleft)
    {
      Terror = ADistance - Inertial.rotation(degrees); 
    }
    else
    {
      Terror = ADistance - Inertial.rotation(degrees)*-1; 
    }
    int Dertive = Terror-prevError;
    int Power = (Terror*TkP) + (Dertive*TkD);
    prevError = Terror;
    if (Aleft)
    {
      FR.spin(forward, Power, voltageUnits::volt);
      BR.spin(forward, Power, voltageUnits::volt);
      FL.spin(forward, Power, voltageUnits::volt);
      BL.spin(forward, Power, voltageUnits::volt);
      wait(20, msec);
    }
    else
    {
      FR.spin(reverse, Power, voltageUnits::volt);
      BR.spin(reverse, Power, voltageUnits::volt);
      FL.spin(reverse, Power, voltageUnits::volt);
      BL.spin(reverse, Power, voltageUnits::volt);
      wait(20, msec);
    }
  }
}

////

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
}

int AutonScreener()
{
  while (true)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(GPS.xPosition(mm));
    Brain.Screen.print(" ");
    Brain.Screen.print(GPS.yPosition(mm));
    Brain.Screen.newLine();
    Brain.Screen.print("Angle ");
    Brain.Screen.print(GPS.heading(degrees));
    Brain.Screen.newLine();
    Brain.Screen.print("GPS Qual");
    Brain.Screen.print(GPS.quality());
    Brain.Screen.newLine();
    Brain.Screen.print("Left P ");
    Brain.Screen.print((FL.velocity(rpm) + BL.velocity(rpm)/2));
    Brain.Screen.newLine();
    Brain.Screen.print("Right P ");
    Brain.Screen.print((FR.velocity(rpm) + BR.velocity(rpm)/2));
    Brain.Screen.newLine();
    Brain.Screen.print("Distance ");
    Brain.Screen.print(LDistance);
    Brain.Screen.newLine();
    Brain.Screen.print("error/away ");
    Brain.Screen.print(Terror);
    Brain.Screen.newLine();
    Brain.Screen.print("Tracking ");
    Brain.Screen.print(Inertial.rotation(degrees));
    wait(10, msec);
    /*
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Controller1.Screen.newLine();
    Controller1.Screen.print(RADist);
    wait(10, msec);
    */
  }
  return 0;
}
//
//
//
//
//


void Move(int amount, bool rev, float oft)
{
  task::stop(Fmove);
  task::stop(FTurn);
  task aw(Fmove);
  Arev = rev;
  FmoveReset = true;
  LDistance = amount;
  Brain.Timer.reset();
  waitUntil(Lerror < 0 || Brain.Timer.value() > oft);
  task::stop(Fmove);
  FL.stop(hold);
  FR.stop(hold);
  BL.stop(hold);
  BR.stop(hold);
  Controller1.Screen.print("M");
}

void Turn(int amount, bool rev, float oft)
{
  task::stop(FTurn);
  task::stop(Fmove);
  task::stop(TrainDrive);
  task aw(FTurn);
  Aleft = rev;
  FTurnReset = true;
  TDistance = amount;
  Brain.Timer.reset();
  if (TDistance > 35)
  {
    waitUntil(Terror < 5 || Brain.Timer.value() > oft);
  }
  else
  {
    waitUntil(Terror < 0.2 || Brain.Timer.value() > oft);
  }
  task::stop(FTurn);
  FL.stop(hold);
  FR.stop(hold);
  BL.stop(hold);
  BR.stop(hold);
  task f(TrainDrive);
  Controller1.Screen.print("T");
}

void TurnTo(int spot, bool rev, float oft)
{
  task::stop(FTurn);
  task::stop(Fmove);
  task::stop(TrainDrive);
  task aw(FTurn);
  Aleft = rev;
  FTurnReset = true;
  TDistance = std::abs(spot-Dir);
  Brain.Timer.reset();
  if (TDistance > 35)
  {
    waitUntil(Terror < 5 || Brain.Timer.value() > oft);
  }
  else
  {
    waitUntil(Terror < 0.2 || Brain.Timer.value() > oft);
  }
  wait(100, msec);  
  task::stop(FTurn);
  FL.stop(hold);
  FR.stop(hold);
  BL.stop(hold);
  BR.stop(hold);
  task f(TrainDrive);
  Controller1.Screen.print("T");
}

//1cm = 10 mm
//360 deg = 219.44 mm  
// desired mm / 0.609556 = degrees needed to travel thaat far
void MoveTo(int Location, bool rev, float oft, bool x) //dont use
{
  task::stop(Fmove);
  task::stop(FTurn);
  task aw(Fmove);
  Arev = rev;
  FmoveReset = true;
  float di = 0;
  if (x)
  {
    di = std::abs(Location - X);
    LDistance = di / 0.609556;
  }
  else
  {
    di = std::abs(Location - Y);
    LDistance = di / 0.609556;
  }
  Brain.Timer.reset();
  waitUntil(Lerror < 0 || Brain.Timer.value() > oft);
  task::stop(Fmove);
  FL.stop(hold);
  FR.stop(hold);
  BL.stop(hold);
  BR.stop(hold);
  Controller1.Screen.print("M");
}

int TDist = 0;
bool Left = true;

float error = 0;
float PAway = 0;

int TSpeed()
{
  float Power = 0;
  Inertial.setHeading(0,degrees);

  while (true)
  {
    if (Left)
    {
      if (Inertial.heading(degrees) > 0)
      {
        error = TDist - Inertial.heading(degrees);
      }
      else
      {
        error = TDist - Inertial.heading(degrees);
      }
    }
    else
    {
      if (Inertial.heading(degrees) < 0)
      {
        error = TDist - Inertial.heading(degrees);
      }
      else
      {
        error = TDist + Inertial.heading(degrees);
      }
    }

    PAway = TDist / Inertial.heading(degrees);

    Power = error/1;

    if (Left)
    {
      FL.spin(forward, (Power * 0.36)/1, voltageUnits::volt);
      FR.spin(reverse, Power * 0.36, voltageUnits::volt);
      BL.spin(forward, (Power * 0.36)/1, voltageUnits::volt);
      BR.spin(reverse, Power * 0.36, voltageUnits::volt);
    }
    else
    {
      FL.spin(reverse, Power * 0.36, voltageUnits::volt);
      FR.spin(forward, (Power * 0.36)/1, voltageUnits::volt);
      BL.spin(reverse, Power * 0.36, voltageUnits::volt);
      BR.spin(forward, (Power * 0.36)/1, voltageUnits::volt);
    }
  }
  return 0;
}

void ATurn(int amount, bool rev, float oft)
{
  FL.setPosition(0,degrees);
  FR.setPosition(0,degrees);
  BL.setPosition(0,degrees);
  BR.setPosition(0,degrees);

  TDist = amount;
  Left = rev;
  task::stop(TrainDrive);
  task a(TSpeed);
  Brain.Timer.reset();
  waitUntil(false || Brain.Timer.value() >= oft);
  task::stop(TSpeed);
  task b(TrainDrive);
  FL.stop(hold);
  FR.stop(hold);
  BL.stop(hold);
  BR.stop(hold);
  
  wait(50, msec);
}


int AimAssist()
{
  while (true)
  {
    waitUntil(!Controller1.ButtonA.pressing());
    waitUntil(Controller1.ButtonA.pressing());
    ATurn(1,false, 1);
  }
  return 0;
}

/////////////////////

int pp()
{
  task a1(Position);
  task a(MarkerHandler);
  while (true)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.newLine();
    Brain.Screen.newLine();
    Brain.Screen.newLine();
    Brain.Screen.newLine();
    Brain.Screen.newLine();
    if (Auton == "Left")
    {
      Brain.Screen.print("Left");
    }
    else if (Auton == "Right")
    {
      Brain.Screen.print("Right");
    }
    else
    {
      Brain.Screen.print("error");
    }   
    Brain.Screen.newLine();
    Brain.Screen.print("Distance to M Angle ");
    Brain.Screen.print(RADist);
    Brain.Screen.newLine();
    Brain.Screen.print("Dir");
    Brain.Screen.print(Dir);
    wait(20, msec);
  }
  return 0;
}

/////////////////////
void usercontrol(void)
{
  Controller1.Screen.print("A");
  Winch.setStopping(hold);
  Winch2.setStopping(hold);
  Winch.stop();
  Winch2.stop();
  AutonExpansion = false;
  task::stop(Fmove);
  task::stop(FTurn);
  task::stop(pp);
  task::stop(Position);
  task::stop(MarkerHandler);
  task::stop(Aim);

  task::stop(LAutoRoll);
  task::stop(RAutoRoll);

  task::stop(AutonScreener);

  task::stop(SecondAmendment);
  task::stop(TrainDrive);

  task::stop(Rev);
  task::stop(Suck);
  ///

  task a1(Position);

  task a(MarkerHandler);
  task c(Aim);

  task c2(AimAssist);

  task e(SecondAmendment);
  task f(TrainDrive);

  task l(LAutoRoll);
  task r(RAutoRoll);

  task g(Rev);
  task h(Suck);

  //task i(Roll);
  
  //task popo(Screener);

  task k(ExpansionSafty);
  while(true)
  {
    wait(230, sec);
  }
}

/*
class SButton
{
  public:
    int Type;   
    int x1;
    int y1;
    int x2;
    int y2;
};
*/
void pre_auton(void)
{
  /*SButton carObj1;
  int RedBX1 = 10;
  int RedBY1 = -10;
  int RedBX2 = 100;
  int RedBY2 = -100;
  Brain.Screen.setFillColor(red);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(RedBX1, RedBY1, RedBX2, RedBY2);
  int BlueBX1 = 10;
  int BlueBY1 = -10;
  int BlueBX2 = 100;
  int BlueBY2 = -100;
  Brain.Screen.setFillColor(blue);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(BlueBX1, BlueBY1, BlueBX2, BlueBY2);
  waitUntil(Brain.Screen.pressing());
  if (Brain.Screen.xPosition() > RedBX1 && Brain.Screen.xPosition() < RedBX2   &&      Brain.Screen.yPosition() < RedBY1 && Brain.Screen.yPosition() > RedBY2 )
  {
    Team = "Red";
  }
  if (Brain.Screen.xPosition() > BlueBX1 && Brain.Screen.xPosition() < BlueBX2     &&     Brain.Screen.yPosition() < BlueBY1 && Brain.Screen.yPosition() > BlueBY2 )
  {
    Team = "Blue";
  }
  Brain.Screen.clearScreen();
  */
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
  
}
/////////////////////

void Shoot()
{
  AutonShoot = false;
  wait(50,msec);
  AutonShoot = true;
  wait(50, msec);
  AutonShoot = false;
}

void autonomous(void)
{
  Winch.setStopping(hold);
  Winch2.setStopping(hold);
  Winch.stop();
  Winch2.stop();

  task::stop(pp);
  task::stop(Position);

  task a1(Position);
  //task cb(FTurn);
  task d(MarkerHandler);                      
  task f(Aim);

  task g(LAutoRoll);
  task h(RAutoRoll);

  task::stop(Screener);
  //task i(AutonScreener);

  task gq(Rev);
  task hq(Suck);
  if (Auton == "Right")
  {
    //INSTRUCTIONS: place on top right part of tile alligned with the intersection between tiles facing stright so roller is straight looking at the wall
    AutonShoot = false;
    task j(SecondAmendment);
    //Right Roller + 2 disk

    if(!Button.pressing())
    {
      waitUntil(Button.pressing());
    }
    Shoot();
    wait(1.5, sec);

    task::stop(SecondAmendment);
    task jws(SecondAmendment);

    Intake.setVelocity(600, rpm);
    Intake2.setVelocity(600, rpm);
    Intake.spin(forward);
    Intake2.spin(forward);
    waitUntil(Button.pressing());
    Intake.stop();
    Intake2.stop();
    Shoot();
  
    wait(1, sec);

    if (Team == "Red")
    {
      TurnTo(90, true, 1);
      TurnTo(90, true, 1);
    }
    else
    {
      TurnTo(270, true, 1);
      TurnTo(270, true, 1);
    }

    Move(800, false, 1);

    Turn(90, false, 1);
    if (Team == "Blue")
    {
      Intake.spin(forward, 200, rpm);
      Intake2.spin(forward, 200, rpm);
    }
    else
    {
      Intake.spin(forward, -200, rpm);
      Intake2.spin(forward, -200, rpm);
    }
    Move(300, true, 1);
    wait(1, sec);
    Move(300, false, 1);
  }
  if (Auton == "Left")
  {
    //INSTRUCTIONS: Aim mussle at goal and make sure it can easily back up and get roller
    task j(SecondAmendment);
    Controller1.Screen.print("q");
    if(!Button.pressing())
    {
      waitUntil(Button.pressing());
    }
    Shoot();
    wait(1.5, sec);

    task::stop(SecondAmendment);
    task jws(SecondAmendment);

    Intake.setVelocity(600, rpm);
    Intake2.setVelocity(600, rpm);
    Intake.spin(forward);
    Intake2.spin(forward);
    waitUntil(Button.pressing());
    Intake.stop();
    Intake2.stop();
    Shoot();

  
    wait(1, sec);

    Intake.spin(forward, 200, rpm);
    Intake2.spin(forward, 200, rpm);
    Move(400, true, 1);
    //
  }
}

int holder()
{
  while(true)
  {
    Winch.setStopping(hold);
    Winch2.setStopping(hold);
    Winch.stop();
    Winch2.stop();

    wait(20, msec);
  }
  return 0;
}

int main() 
{
  //task qwe(holder);
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Controller1.Screen.print("w");
  Inertial.calibrate();
  wait(3, sec);
  Controller1.rumble(rumbleLong);
  Controller1.Screen.print("w");

  waitUntil(Brain.Screen.pressing());
  if (Brain.Screen.xPosition() < 240)
  {
    Auton = "Left";
  }
  else
  {
    Auton = "Right";
  }

  if (Auton == "Left")
  {
    Brain.Screen.clearLine();
    Brain.Screen.print("Left");
    Controller1.Screen.clearLine();
    Controller1.Screen.print("Left");
  }
  else if (Auton == "Right")
  {
    Brain.Screen.clearLine();
    Brain.Screen.print("Right");
    Controller1.Screen.clearLine();
    Controller1.Screen.print("Right");
  }
  else
  {
    Brain.Screen.clearLine();
    Brain.Screen.print("error");
    Controller1.Screen.clearLine();
    Controller1.Screen.print("error");
  }   
  //task aq(pp);
  Competition.drivercontrol(usercontrol);
  Competition.autonomous(autonomous);
  
  while (true) 
  {
    wait(20, msec);    
  }
}
//1cm = 10 mm
//360 deg = 219.44 mm  
// desired mm / 0.609556 = degrees needed to travel thaat far