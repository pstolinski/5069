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
motor driveTrainLeft = motor(PORT1, ratio18_1, false);
motor driveTrainRight = motor(PORT2, ratio18_1, true);
/*vex-vision-config:begin*/
signature VisionSensor__SIG_BLUE = signature (1, -2913, -1607, -2260, 7351, 11879, 9615, 1, 0);
signature VisionSensor__SIG_RED = signature (2, 6127, 8429, 7278, -511, 505, -3, 2.2, 0);
signature VisionSensor__SIG_GREEN = signature (3, -5851, -5359, -5605, -5923, -5481, -5702, 6, 0);
signature VisionSensor__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vision VisionSensor = vision (PORT9, 50, VisionSensor__SIG_BLUE, VisionSensor__SIG_RED, VisionSensor__SIG_GREEN, VisionSensor__SIG_4, VisionSensor__SIG_5);
/*vex-vision-config:end*/
/*vex-vision-config:begin*/
vision VisionTwo = vision (PORT10, 50);
/*vex-vision-config:end*/

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