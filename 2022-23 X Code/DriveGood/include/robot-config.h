using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;
extern motor flywheelBottom;
extern motor flywheelTop;
extern motor intakeMotor;
extern rotation flywheelRotation;
extern controller Controller1;
extern gps GPS;
extern led triggerPneumatic;
extern inertial inertialSensor;
extern led flapPneumatic;
extern signature VisionSensor__SIG_RED;
extern signature VisionSensor__SIG_BLUE;
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