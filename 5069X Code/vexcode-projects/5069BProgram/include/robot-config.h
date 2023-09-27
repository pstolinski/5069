using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor DRFront;
extern motor DRBack;
extern motor DLFront;
extern motor DLBack;
extern motor LIntake;
extern motor RIntake;
extern motor FRoller;
extern motor BRoller;
extern controller Controller1;
extern optical OpticalSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );