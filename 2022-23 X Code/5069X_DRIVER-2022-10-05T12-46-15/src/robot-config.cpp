#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LF = motor(PORT20, ratio18_1, true);
motor LB = motor(PORT19, ratio18_1, false);
motor RF = motor(PORT12, ratio18_1, false);
motor RB = motor(PORT15, ratio18_1, true);
motor FlywheelBottom = motor(PORT13, ratio18_1, true);
motor FlywheelTop = motor(PORT14, ratio18_1, false);
motor Intake = motor(PORT16, ratio18_1, false);
rotation FlywheelR = rotation(PORT11, false);
controller Controller1 = controller(primary);
gps GPS = gps(PORT17, 0.00, -196.85, mm, 180);
led Pneumatic = led(Brain.ThreeWirePort.H);
inertial Inertial = inertial(PORT18);
led FlickPneumatic = led(Brain.ThreeWirePort.G);

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