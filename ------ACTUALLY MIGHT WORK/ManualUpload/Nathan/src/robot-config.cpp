#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LF = motor(PORT16, ratio18_1, false);
motor LB = motor(PORT11, ratio18_1, true);
motor RF = motor(PORT10, ratio18_1, true);
motor RB = motor(PORT20, ratio18_1, false);
motor FlywheelMotorA = motor(PORT3, ratio18_1, false);
motor FlywheelMotorB = motor(PORT4, ratio18_1, true);
motor_group Flywheel = motor_group(FlywheelMotorA, FlywheelMotorB);
led Pneumatic = led(Brain.ThreeWirePort.A);
gps GPS = gps(PORT15, 101.60, 165.10, mm, 0);
motor IntakeMotorA = motor(PORT13, ratio18_1, true);
motor IntakeMotorB = motor(PORT12, ratio18_1, true);
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