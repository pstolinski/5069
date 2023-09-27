using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor driveTrainLeft;
extern motor driveTrainRight;
extern motor ejectionSpinner;
extern motor armMotor;
extern controller Controller1;
extern signature VisionSensor__SIG_RED;
extern signature VisionSensor__SIG_2;
extern signature VisionSensor__SIG_3;
extern signature VisionSensor__SIG_4;
extern signature VisionSensor__SIG_5;
extern signature VisionSensor__SIG_6;
extern signature VisionSensor__SIG_7;
extern vision VisionSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );