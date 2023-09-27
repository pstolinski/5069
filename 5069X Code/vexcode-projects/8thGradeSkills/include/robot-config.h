#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
//
using namespace vex;
vex::brain Brain;
vex::motor M3FlipperLeft (vex::PORT1, vex::gearSetting::ratio36_1,false);
vex::motor M4FlipperRight (vex::PORT10, vex::gearSetting::ratio36_1,false);
vex::motor M2DriveLeft (vex::PORT11, vex::gearSetting::ratio18_1,false);
vex::motor M1DriveRight (vex::PORT20, vex::gearSetting::ratio18_1,true);
vex::controller Controller1;