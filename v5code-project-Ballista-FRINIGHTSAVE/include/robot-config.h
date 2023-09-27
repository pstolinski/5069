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
extern gps GPS;
extern motor Winch2;
extern triport Expander21;
extern encoder Tracking;
extern led Expansion1;
extern led Expansion2;
extern led Expansion3;
extern led Expansion4;
extern optical LeftB;
extern motor_group Intake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );