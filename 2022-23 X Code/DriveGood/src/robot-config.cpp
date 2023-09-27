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
motor flywheelBottom = motor(PORT13, ratio18_1, true);
motor flywheelTop = motor(PORT14, ratio18_1, false);
motor intakeMotor = motor(PORT16, ratio18_1, false);
rotation flywheelRotation = rotation(PORT11, false);
controller Controller1 = controller(primary);
gps GPS = gps(PORT17, 0.00, -196.85, mm, 180);
led triggerPneumatic = led(Brain.ThreeWirePort.H);
inertial inertialSensor = inertial(PORT18);
led flapPneumatic = led(Brain.ThreeWirePort.G);
/*vex-vision-config:begin*/
signature VisionSensor__SIG_RED = signature (1, 7525, 8949, 8238, -2039, -605, -1322, 4.2, 0);
signature VisionSensor__SIG_BLUE = signature (2, -2467, -1639, -2053, 6125, 8279, 7202, 4.9, 0);
vision VisionSensor = vision (PORT1, 50, VisionSensor__SIG_RED, VisionSensor__SIG_BLUE);
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