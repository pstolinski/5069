#include "main.h"

pros::Controller controller(CONTROLLER_MASTER);
pros::Motor driveTrainL(1);
pros::Motor driveTrainR(2, true);

void tareMotors(){
  driveTrainL.tare_position();
  driveTrainR.tare_position();
}

void moveDriveTrain(int velocityL, int velocityR){
  driveTrainL.move_velocity(velocityL*100);
	driveTrainR.move_velocity(velocityR*100);
}

void initalize(){}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	tareMotors();
  while(true){
	moveDriveTrain(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
	controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
	}
}
