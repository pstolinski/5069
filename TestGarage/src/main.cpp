#include "main.h"

pros::Controller controller(CONTROLLER_MASTER);
pros::Motor DriveTrainR(1, true);
pros::Motor DriveTrainL(2);
pros::Motor ArmExtension(3);
pros::Motor Claw(4, true);

bool armMoving = false;
bool clawMoving = false;
void setDriveTrain(int velocityL, int velocityR){
 DriveTrainL.move_velocity(velocityL);
 DriveTrainR.move_velocity(velocityR);
}

void moveArm(bool isL1Pressed, bool isL2Pressed){
  if (isL1Pressed||isL2Pressed) {
    if(isL1Pressed){
     ArmExtension.move_velocity(100);
     armMoving=true;
   } else if (isL2Pressed) {
     ArmExtension.move_velocity(-100);
     armMoving=true;
   }
   armMoving=false;
}else {
  ArmExtension.move_velocity(0);
  armMoving=false;
}
}

void moveClaw(bool isR1Pressed, bool isR2Pressed){
 if (isR1Pressed||isR2Pressed) {
   if(isR1Pressed){
    Claw.move_velocity(100);
    clawMoving=true;
  } else if (isR2Pressed) {
    Claw.move_velocity(-100);
    clawMoving = true;
  }
  clawMoving = false;
}else {
  Claw.move_velocity(0);
  clawMoving=false;
}
}

void checkArmMove(){
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) ||
  controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){}
  else if(!armMoving){
  ArmExtension.move_absolute(ArmExtension.get_position(), 0);
  pros::delay(10);
}
}

void checkClawMove(){
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) ||
  controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){}
  else if(!clawMoving){
  Claw.move_absolute(Claw.get_position(), 0);
  pros::delay(10);
}
}

void tareMotors(){
  DriveTrainL.tare_position();
  DriveTrainR.tare_position();
  ArmExtension.tare_position();
  Claw.tare_position();
}

void initialize()
{

}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
  tareMotors();
  while(true){
  		//Tank Mode
  		setDriveTrain(
  			controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
  			controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)
  		);

  		moveArm(
  			controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1),
  			controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)
  		);

  		moveClaw(
  			controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1),
  			controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)
  		);

      checkArmMove();
      checkClawMove();

    pros::delay(20);
  }
}
