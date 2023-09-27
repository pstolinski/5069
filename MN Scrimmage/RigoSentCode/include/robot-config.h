using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern rotation Rotation;
extern motor Winch;
extern limit Button;
extern motor FL;
extern motor BL;
extern motor FR;
extern motor BR;
extern motor Intake;
extern gps GPS;
extern motor Winch2;
extern triport Expander21;
extern motor Intake2;
extern encoder Tracking;
extern optical RightB;
extern optical LeftB;
extern led Expansion1;
extern led Expansion2;
extern led Expansion3;
extern led Expansion4;
extern inertial Inertial;
extern inertial TInertial;
extern motor Intake3;
extern controller Controller2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );