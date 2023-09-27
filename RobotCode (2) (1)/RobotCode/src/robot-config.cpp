#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FR = motor(PORT1, ratio18_1, false);
motor BR = motor(PORT2, ratio18_1, false);
motor FL = motor(PORT3, ratio18_1, false);
motor BL = motor(PORT4, ratio18_1, false);
motor ForkF = motor(PORT5, ratio18_1, false);
motor ForkR = motor(PORT6, ratio18_1, false);
digital_out SnowL = digital_out(Brain.ThreeWirePort.B);
digital_out SnowR = digital_out(Brain.ThreeWirePort.C);
motor ForkB = motor(PORT7, ratio18_1, false);
motor ForkL = motor(PORT8, ratio18_1, false);

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