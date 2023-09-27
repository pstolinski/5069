using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor FR;
extern motor FL;
extern motor BR;
extern motor BL;
extern motor DriveBooster;
extern motor Tread;
extern motor_group MotorGroup1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );