using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor DL1;
extern motor DL2;
extern motor DR1;
extern motor DR2;
extern motor Intake;
extern controller Controller1;
extern motor Claw;
extern motor_group ArmGroup;
extern led Pnuematic;
extern inertial Inertial;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );