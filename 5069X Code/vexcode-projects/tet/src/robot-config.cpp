#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftIntakeMotor = motor(PORT3, ratio18_1, false);
motor rightIntakeMotor = motor(PORT4, ratio18_1, true);
motor intakeSpinner = motor(PORT5, ratio18_1, true);
motor ejectionSpinner = motor(PORT6, ratio18_1, false);
motor middleSpinner = motor(PORT7, ratio18_1, false);
motor outtakeSpinner = motor(PORT8, ratio6_1, true);
motor driveTrainLeft = motor(PORT1, ratio18_1, true);
motor driveTrainRight = motor(PORT2, ratio18_1, false);
/*vex-vision-config:begin*/
vision VisionTwo = vision (PORT10, 50);
/*vex-vision-config:end*/
optical OpticalSensor = optical(PORT9);

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