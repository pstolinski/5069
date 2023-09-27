#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor L1 = motor(PORT14, ratio6_1, true);
motor L2 = motor(PORT15, ratio6_1, false);
motor R1 = motor(PORT18, ratio6_1, true);
motor R2 = motor(PORT12, ratio6_1, false);
motor Winch = motor(PORT17, ratio18_1, false);
distance WDist = distance(PORT3);
motor Intake = motor(PORT10, ratio6_1, false);
motor L3 = motor(PORT16, ratio6_1, false);
motor R3 = motor(PORT13, ratio6_1, true);

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