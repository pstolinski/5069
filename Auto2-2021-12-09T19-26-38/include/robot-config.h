using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor FR;
extern motor FL;
extern motor BR;
extern motor BL;
extern motor_group MotorGroup1;
extern motor Tread;
extern digital_out DigitalOutB;
extern digital_out DigitalOutC;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );