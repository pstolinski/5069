using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern drivetrain Drivetrain;
extern motor IntakeSpinner;
extern motor EjectionSpinner;
extern motor MiddleSpinner;
extern motor ShooterSpinner;
extern motor LeftIntake;
extern motor RightIntake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );