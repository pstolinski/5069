using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor FR;
extern motor BR;
extern motor FL;
extern motor BL;
extern motor ForkF;
extern motor ForkR;
extern digital_out SnowL;
extern digital_out SnowR;
extern motor ForkB;
extern motor ForkL;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );