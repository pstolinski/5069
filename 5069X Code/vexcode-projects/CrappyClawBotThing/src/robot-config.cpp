#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor driveTrainLeft = motor(PORT4, ratio18_1, true);
motor driveTrainRight = motor(PORT3, ratio18_1, false);
motor ejectionSpinner = motor(PORT2, ratio18_1, false);
motor armMotor = motor(PORT1, ratio18_1, true);
controller Controller1 = controller(primary);
/*vex-vision-config:begin*/
signature VisionSensor__SIG_RED = signature (1, 5591, 8427, 7009, -1229, 299, -465, 1.6, 0);
vision VisionSensor = vision (PORT5, 50, VisionSensor__SIG_RED);
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