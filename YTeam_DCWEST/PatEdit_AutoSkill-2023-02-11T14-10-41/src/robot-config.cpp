#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Motor17 = motor(PORT17, ratio36_1, true);
motor Motor18 = motor(PORT18, ratio36_1, false);
motor Motor15 = motor(PORT15, ratio18_1, true);
motor Motor16 = motor(PORT16, ratio18_1, true);
led Pneu = led(Brain.ThreeWirePort.A);
motor leftMotorA = motor(PORT13, ratio18_1, false);
motor leftMotorB = motor(PORT14, ratio18_1, false);
motor rightMotorA = motor(PORT2, ratio18_1, true);
motor rightMotorB = motor(PORT4, ratio18_1, true);

controller Controller1 = controller(primary);
led VPneu = led(Brain.ThreeWirePort.D);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}