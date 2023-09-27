using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;
extern motor FlywheelBottom;
extern motor FlywheelTop;
extern motor Intake;
extern rotation FlywheelR;
extern controller Controller1;
extern gps GPS;
extern led Pneumatic;
extern inertial Inertial;
extern led FlickPneumatic;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );