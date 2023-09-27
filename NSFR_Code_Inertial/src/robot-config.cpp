#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor DL1 = motor(PORT1, ratio18_1, false);
motor DL2 = motor(PORT13, ratio18_1, true);
motor DR1 = motor(PORT10, ratio18_1, true);
motor DR2 = motor(PORT19, ratio18_1, false);
motor Intake = motor(PORT15, ratio18_1, true);
controller Controller1 = controller(primary);
motor Claw = motor(PORT12, ratio18_1, false);
motor ArmGroupMotorA = motor(PORT20, ratio18_1, true);
motor ArmGroupMotorB = motor(PORT11, ratio18_1, false);
motor_group ArmGroup = motor_group(ArmGroupMotorA, ArmGroupMotorB);
led Pnuematic = led(Brain.ThreeWirePort.C);
inertial Inertial = inertial(PORT21);

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