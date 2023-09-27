#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Clamp = motor(PORT8, ratio18_1, false);
motor HiLiftMotorA = motor(PORT16, ratio18_1, false);
motor HiLiftMotorB = motor(PORT6, ratio18_1, false);
motor_group HiLift = motor_group(HiLiftMotorA, HiLiftMotorB);
/*vex-vision-config:begin*/
signature VisionSensor__SIG_RED = signature (1, 2427, 3097, 2762, -4035, -3579, -3807, 2.5, 0);
vision VisionSensor = vision (PORT11, 50, VisionSensor__SIG_RED);
/*vex-vision-config:end*/
motor FL = motor(PORT19, ratio18_1, true);
motor FR = motor(PORT9, ratio18_1, false);
motor BL = motor(PORT20, ratio18_1, false);
motor BR = motor(PORT10, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}