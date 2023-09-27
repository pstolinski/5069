#include "main.h"

pros::Controller controller(CONTROLLER_MASTER);
pros::Motor intakeMotorT(1);
pros::Motor intakeMotorB(2, true);
pros::Motor driveTrainLF(3);
pros::Motor driveTrainLR(4);
pros::Motor driveTrainRF(5, true);
pros::Motor driveTrainRR(6, true);
pros::Vision visionSensor(7);

int shifter = 1;

void tareMotors(){
  intakeMotorT.tare_position();
  intakeMotorB.tare_position();
  driveTrainLF.tare_position();
  driveTrainLR.tare_position();
  driveTrainRF.tare_position();
  driveTrainRR.tare_position();
}

void moveDriveTrain(int velocityL, int velocityR){
  if(shifter == 1){
    driveTrainLF.move_velocity(velocityL/2);
    driveTrainLR.move_velocity(velocityL/2);
    driveTrainRF.move_velocity(velocityR/2);
    driveTrainRR.move_velocity(velocityR/2);
  }
  if(shifter == 2){
    driveTrainLF.move_velocity(velocityL/.5);
    driveTrainLR.move_velocity(velocityL/.5);
    driveTrainRF.move_velocity(velocityR/.5);
    driveTrainRR.move_velocity(velocityR/.5);
  }
  if(shifter == 3){
    driveTrainLF.move_velocity(velocityL);
    driveTrainLR.move_velocity(velocityL);
    driveTrainRF.move_velocity(velocityR);
    driveTrainRR.move_velocity(velocityR);
  }
  if(shifter == 4){
    driveTrainLF.move_velocity(velocityL*2);
    driveTrainLR.move_velocity(velocityL*2);
    driveTrainRF.move_velocity(velocityR*2);
    driveTrainRR.move_velocity(velocityR*2);
  }
  if(shifter == 5){
    driveTrainLF.move_velocity(velocityL*3);
    driveTrainLR.move_velocity(velocityL*3);
    driveTrainRF.move_velocity(velocityR*3);
    driveTrainRR.move_velocity(velocityR*3);
  }
}

void moveBottomElevator(bool isL1Pressed, bool isL2Pressed){
  if(isL1Pressed){
    intakeMotorB.move_velocity(500);
  }
  else if(isL2Pressed){
    intakeMotorB.move_velocity(-500);
  }
  else{
    intakeMotorB.move_velocity(0);
  }
}

void moveTopElevator(bool isR1Pressed, bool isR2Pressed){
  if(isR1Pressed){
    intakeMotorT.move_velocity(1000);
  }
  else if(isR2Pressed){
    intakeMotorT.move_velocity(-1000);
  }
  else{
    intakeMotorT.move_velocity(0);
  }
}

void shiftUp(bool xPressed){
  if(xPressed && shifter < 5){
  shifter++;
  controller.print(0, 0, "High Gear");
}
}

void shiftDown(bool aPressed){
  if(aPressed && shifter > 1){
  shifter--;
  controller.print(0, 0, "Low Gear");
}
}

void initialize(){

}

void disabled(){}

void competition_initialize(){

}

void autonomous(){
  //tasks to acheive:
   //forward
   //pick up the ball
   //
//This part is optional with respect to where our starting position is.
//CURRENTLY SET TO LEFT SIDE ON TWO POINT AUTONOMOUS
   driveTrainLF.move_velocity(100);
   driveTrainLR.move_velocity(100);
   driveTrainRF.move_velocity(100);
   driveTrainRR.move_velocity(100);
   pros::delay(2000);

   //Turning the wheels 90 degrees.(From this part onward is plan 2.)
   driveTrainLF.move_velocity(-100);
   driveTrainLR.move_velocity(-100);
   driveTrainRF.move_velocity(100);
   driveTrainRR.move_velocity(100);
   pros::delay(710);
   driveTrainLF.move_velocity(0);
   driveTrainLR.move_velocity(0);
   driveTrainRF.move_velocity(0);
   driveTrainRR.move_velocity(0);
   //After turning,we move forward for 136 centimeter.See attached math.
   driveTrainLF.move_velocity(100);
   driveTrainLR.move_velocity(100);
   driveTrainRF.move_velocity(100);
   driveTrainRR.move_velocity(100);
   pros::delay(2500);
   driveTrainLF.move_velocity(0);
   driveTrainLR.move_velocity(0);
   driveTrainRF.move_velocity(0);
   driveTrainRR.move_velocity(0);
   //Reverse intake into the tower.
   intakeMotorB.move_velocity(350);
   intakeMotorT.move_velocity(700);
   pros::delay(1000);
   intakeMotorB.move_velocity(0);
   intakeMotorT.move_velocity(0);
   driveTrainLF.move_velocity(-100);
   driveTrainLR.move_velocity(-100);
   driveTrainRF.move_velocity(-100);
   driveTrainRR.move_velocity(-100);
   pros::delay(750);
   driveTrainLF.move_velocity(0);
   driveTrainLR.move_velocity(0);
   driveTrainRF.move_velocity(0);
   driveTrainRR.move_velocity(0);
   //END OF PHASE ONE
   driveTrainLF.move_velocity(-100);
   driveTrainLR.move_velocity(-100);
   driveTrainRF.move_velocity(100);
   driveTrainRR.move_velocity(100);
   pros::delay(510);
   driveTrainLF.move_velocity(100);
   driveTrainLR.move_velocity(100);
   driveTrainRF.move_velocity(100);
   driveTrainRR.move_velocity(100);
   pros::delay(1900);
   driveTrainLF.move_velocity(0);
   driveTrainLR.move_velocity(0);
   driveTrainRF.move_velocity(0);
   driveTrainRR.move_velocity(0);
   pros::delay(10);
   intakeMotorB.move_velocity(400);
   intakeMotorT.move_velocity(700);
   pros::delay(1100);
   intakeMotorB.move_velocity(0);
   intakeMotorT.move_velocity(0);
   driveTrainLF.move_velocity(-100);
   driveTrainLR.move_velocity(-100);
   driveTrainRF.move_velocity(-100);
   driveTrainRR.move_velocity(-100);
   pros::delay(1000);
   driveTrainLF.move_velocity(0);
   driveTrainLR.move_velocity(0);
   driveTrainRF.move_velocity(0);
   driveTrainRR.move_velocity(0);
}

void opcontrol() {
  tareMotors();
  while(true){
    moveDriveTrain(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
    controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

    moveBottomElevator(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1),
    controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));

    moveTopElevator(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1),
    controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));

    shiftUp(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X));

    shiftDown(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A));

    pros::delay(10);
  }
}
