#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor DRFront = motor(PORT11, ratio18_1, true);
motor DRBack = motor(PORT12, ratio18_1, false);
motor DLFront = motor(PORT13, ratio18_1, false);
motor DLBack = motor(PORT14, ratio18_1, true);
motor LIntake = motor(PORT15, ratio18_1, true);
motor RIntake = motor(PORT16, ratio18_1, false);
motor FRoller = motor(PORT17, ratio18_1, false);
motor BRoller = motor(PORT18, ratio18_1, false);
controller Controller1 = controller(primary);
optical OpticalSensor = optical(PORT19);

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