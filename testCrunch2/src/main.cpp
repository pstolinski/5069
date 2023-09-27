#include "main.h"

pros::Controller controller(CONTROLLER_MASTER);
pros::Motor DriveTrainL(2);
pros::Motor DriveTrainR(1, true);
pros::Motor ConveyorBelt(4);
pros::Motor ArmMove(3);
/**
 * Controls the Drive Train for the bot with a left and right velocity.
 */
void setDriveTrain(int velocityL, int velocityR){
DriveTrainL.move_velocity(velocityL);
DriveTrainR.move_velocity(velocityR);
}
/**
 * Tares all of the motors for the robot.
 */
 void tareMotors(){
DriveTrainL.tare_position();
DriveTrainR.tare_position();
   ConveyorBelt.tare_position();
   ArmMove.tare_position();
 }
 /**
 * Controls the running of the intake motors.
 * Only runs if either L1 or L2 is pressed but not both
 * L1 = backwards
 * L2 = forwards
 */
void setIntake(bool isL1Pressed, bool isL2Pressed){

if(isL1Pressed == true && isL2Pressed == false){
ConveyorBelt.move_velocity(255);
}else if(isL2Pressed  && !isL2Pressed){
ConveyorBelt.move_velocity(-255);
}
}


void setArmMovement(bool isR1Pressed, bool isR2Pressed){
if(isR1Pressed == true && isR2Pressed == false){
ArmMove.move_velocity(100);
}
if(isR2Pressed == true && isR1Pressed == false){
ArmMove.move_velocity(-100);
}
}

void moveHorizontal(bool isR2Pressed, bool isL2Pressed){
	if(isL2Pressed == true && isR2Pressed == false){
		DriveTrainL.move_velocity(100);
	}
	else if(isR2Pressed == true && isL2Pressed == false){
		DriveTrainR.move_velocity(-100);
	}
}

void opcontrol(){
tareMotors();
while (true) {
//Tank Mode
setDriveTrain(
controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)
);

//Buttons L1 and R1 for Controlling the Intake
setIntake(
controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1),
controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
);

//Buttons L2 and R2 for Controlling the Horizontal Translation of the bot
moveHorizontal(
controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2),
controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
