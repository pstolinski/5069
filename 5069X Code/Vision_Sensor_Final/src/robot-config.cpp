#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature VisionSensor__SIG_YELLOW = signature (1, 2675, 3325, 3000, -4605, -4389, -4497, 6.4, 0);
vision VisionSensor = vision (PORT21, 50, VisionSensor__SIG_YELLOW);
/*vex-vision-config:end*/
motor FL = motor(PORT12, ratio18_1, true);
motor FR = motor(PORT11, ratio18_1, false);
motor BL = motor(PORT14, ratio18_1, true);
motor BR = motor(PORT13, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}