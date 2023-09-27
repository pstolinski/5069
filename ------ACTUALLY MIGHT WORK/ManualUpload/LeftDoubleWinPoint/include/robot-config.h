using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor DriveBooster;
extern motor Tread;
extern motor_group MotorGroup1;
extern smartdrive Drivetrain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );