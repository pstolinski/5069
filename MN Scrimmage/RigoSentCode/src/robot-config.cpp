#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
triport Expander21 = triport(PORT21);
controller Controller1 = controller(primary);
rotation Rotation = rotation(PORT5, true);
motor Winch = motor(PORT14, ratio18_1, false);
limit Button = limit(Brain.ThreeWirePort.E);
motor FL = motor(PORT11, ratio36_1, false);
motor BL = motor(PORT12, ratio36_1, false);
motor FR = motor(PORT17, ratio36_1, false);
motor BR = motor(PORT15, ratio36_1, false);
motor Intake = motor(PORT13, ratio6_1, false);
gps GPS = gps(PORT7, 0.00, -160.00, mm, 180);
motor Winch2 = motor(PORT20, ratio18_1, true);
motor Intake2 = motor(PORT16, ratio6_1, false);
encoder Tracking = encoder(Brain.ThreeWirePort.G);
optical RightB = optical(PORT9);
optical LeftB = optical(PORT2);
led Expansion1 = led(Brain.ThreeWirePort.A);
led Expansion2 = led(Brain.ThreeWirePort.B);
led Expansion3 = led(Brain.ThreeWirePort.C);
led Expansion4 = led(Brain.ThreeWirePort.D);
inertial Inertial = inertial(PORT3);
inertial TInertial = inertial(PORT4);
motor Intake3 = motor(PORT18, ratio6_1, true);
controller Controller2 = controller(partner);

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