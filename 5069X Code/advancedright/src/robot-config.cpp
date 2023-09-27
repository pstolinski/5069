#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FR = motor(PORT11, ratio18_1, false);
motor FL = motor(PORT12, ratio18_1, true);
motor BR = motor(PORT13, ratio18_1, false);
motor BL = motor(PORT14, ratio18_1, true);
motor Tread = motor(PORT18, ratio18_1, false);
motor MotorGroup1MotorA = motor(PORT17, ratio36_1, true);
motor MotorGroup1MotorB = motor(PORT16, ratio36_1, false);
motor_group MotorGroup1 = motor_group(MotorGroup1MotorA, MotorGroup1MotorB);
digital_out DigitalOutB = digital_out(Brain.ThreeWirePort.B);
digital_out DigitalOutA = digital_out(Brain.ThreeWirePort.A);

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