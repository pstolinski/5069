using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor leftIntakeMotor;
extern motor rightIntakeMotor;
extern motor intakeSpinner;
extern motor ejectionSpinner;
extern motor middleSpinner;
extern motor outtakeSpinner;
extern motor driveTrainLeft;
extern motor driveTrainRight;
extern signature VisionTwo__SIG_1;
extern signature VisionTwo__SIG_2;
extern signature VisionTwo__SIG_3;
extern signature VisionTwo__SIG_4;
extern signature VisionTwo__SIG_5;
extern signature VisionTwo__SIG_6;
extern signature VisionTwo__SIG_7;
extern vision VisionTwo;
extern optical OpticalSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );