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
limit Button = limit(Brain.ThreeWirePort.D);
motor FL = motor(PORT11, ratio18_1, false);
motor BL = motor(PORT12, ratio18_1, false);
motor FR = motor(PORT17, ratio18_1, false);
motor BR = motor(PORT18, ratio18_1, false);
gps GPS = gps(PORT7, -100.00, 100.00, mm, 270);
motor Winch2 = motor(PORT20, ratio18_1, true);
encoder Tracking = encoder(Expander21.C);
led Expansion1 = led(Brain.ThreeWirePort.E);
led Expansion2 = led(Brain.ThreeWirePort.F);
led Expansion3 = led(Brain.ThreeWirePort.G);
led Expansion4 = led(Brain.ThreeWirePort.H);
optical LeftB = optical(PORT1);
motor IntakeMotorA = motor(PORT13, ratio18_1, false);
motor IntakeMotorB = motor(PORT16, ratio18_1, false);
motor_group Intake = motor_group(IntakeMotorA, IntakeMotorB);

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