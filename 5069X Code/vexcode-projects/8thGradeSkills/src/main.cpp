#include "robot-config.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                 NOTICE:                                   */
/*                               DO NOT EDIT                                 */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;
vex::rotationUnits rotations = vex::rotationUnits::rev; 

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                 NOTICE:                                   */
/*                               DO NOT EDIT                                 */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
    // All activities that occur before the competition starts
    // Example: clearing encoders, setting servo positions, ...

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                 NOTICE:                                   */
/*                     THESE ARE THE AUTONOMOUS FUNCTIONS.                   */
/*               DO NOT EDIT UNLESS YOU KNOW WHAT YOU ARE DOING.             */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {

    //Change ".setVelocity(<number>, velocityUnits::pct)"" <number> to change motor speed in autonomous program. 
    M2DriveLeft.setVelocity(70, velocityUnits::pct);
    M1DriveRight.setVelocity(70, velocityUnits::pct);

    //Change "int howMany = <number>" <number> to change number of rotations in autonomous program. 
    int howMany = 3;
    M2DriveLeft.startRotateFor(howMany, rotations);
    M1DriveRight.rotateFor(howMany, rotations);

    //Change "vex::task::sleep(<number>);" to change length of pause in autonomous program. 
    vex::task::sleep(250);

    //Change "startRotateFor(<sign>howMany, rotations)" <sign> to change the direction of rotations in autonomous program.
    M2DriveLeft.startRotateFor(-howMany, rotations);
    M1DriveRight.rotateFor(-howMany, rotations);

    //Change "vex::task::sleep(<number>);" to change length of pause in autonomous program. 
    vex::task::sleep(250);

    //Change "howMany = <number>" <number> to change number of rotations in autonomous program.
    M2DriveLeft.startRotateFor(-1.4, rotations);
    M1DriveRight.rotateFor(1.20, rotations);

    //Change "vex::task::sleep(<number>);" to change length of pause in autonomous program. 
    vex::task::sleep(250);

    //Change "int howMany = <number>" <number> to change number of rotations in autonomous program. 

    M2DriveLeft.startRotateFor(2.7, rotations);
    M1DriveRight.rotateFor(2.7, rotations);

    //Change "vex::task::sleep(<number>);" to change length of pause in autonomous program. 
    vex::task::sleep(250);

    //Change "startRotateFor(<sign>howMany, rotations)" <sign> to change the direction of rotations in autonomous program.
    M2DriveLeft.startRotateFor(-howMany, rotations);
    M1DriveRight.rotateFor(-howMany, rotations);

    //Change "vex::task::sleep(<number>);" <number> to change length of pause in autonomous program. 
    vex::task::sleep(250);

}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              User Control Task                             */
/*                                                                            */
/*  This task is used to control your robot during the user control phase of  */
/*  a VEX Competition.                                                        */
/*                                                                            */
/*  You must modify the code to add your own robot specific commands here.    */
/*----------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                 NOTICE:                                   */
/*                     THESE ARE THE DRIVER CONTROL FUNCTIONS.               */
/*                 DO NOT EDIT UNLESS YOU KNOW WHAT YOU ARE DOING.           */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
    int armSpeedPCT = 75;
    // User control code here, inside the loop
    while (1){
        //Drive Control
        //Set the left and right motor to spin forward using the controller Axis values as the velocity value.
        M2DriveLeft.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
        M1DriveRight.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);


        //Flipper Control
        if(Controller1.ButtonR1.pressing()) { //If button up is pressed...
            //...Spin the arm motor forward.
            M3FlipperLeft.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
            M4FlipperRight.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonR2.pressing()) { //If the down button is pressed...
            //...Spin the arm motor backward.
            M3FlipperLeft.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
            M4FlipperRight.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
        }
        else { //If the the up or down button is not pressed...
            //...Stop the arm motor.
            M3FlipperLeft.stop(vex::brakeType::brake);
            M4FlipperRight.stop(vex::brakeType::brake);
        }
        vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
    }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

    //Run the pre-autonomous function. 
    pre_auton();

    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
        vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    

}

/*---------------------------------------------------------------------------*/
/*                                 NOTICE:                                   */
/*                              END OF PROGRAM.                              */
/*---------------------------------------------------------------------------*/
