using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Motor17;
extern motor Motor18;
extern motor Motor15;
extern motor Motor16;
extern led Pneu;
extern drivetrain Drivetrain;
extern controller Controller1;
extern led VPneu;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );