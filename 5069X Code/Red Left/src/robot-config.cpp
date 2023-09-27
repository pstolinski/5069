#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FR = motor(PORT15, ratio18_1, true);
motor FL = motor(PORT17, ratio18_1, false);
motor BR = motor(PORT18, ratio18_1, false);
motor BL = motor(PORT13, ratio18_1, true);
motor DriveBooster = motor(PORT19, ratio18_1, false);
motor Tread = motor(PORT16, ratio18_1, true);
motor MotorGroup1MotorA = motor(PORT14, ratio18_1, false);
motor MotorGroup1MotorB = motor(PORT20, ratio18_1, true);
motor_group MotorGroup1 = motor_group(MotorGroup1MotorA, MotorGroup1MotorB);
/*vex-vision-config:begin*/
vision VisionSensor = vision (PORT11, 50);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}