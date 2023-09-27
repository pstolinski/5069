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

lv_obj_t * myButton;
lv_obj_t * myButtonLabel;
lv_obj_t * myLabel;



lv_style_t myButtonStyleREL; //relesed style
lv_style_t myButtonStylePR; //pressed style

static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons

    if(id == 0)
    {
        char buffer[100];
		sprintf(buffer, "button was clicked %i milliseconds from start", pros::millis());
		lv_label_set_text(myLabel, buffer);
    }

    return LV_RES_OK;
}

void initialize()
{
    lv_style_copy(&myButtonStyleREL, &lv_style_plain);
    myButtonStyleREL.body.main_color = LV_COLOR_MAKE(150, 0, 0);
    myButtonStyleREL.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
    myButtonStyleREL.body.radius = 0;
    myButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);

    lv_style_copy(&myButtonStylePR, &lv_style_plain);
    myButtonStylePR.body.main_color = LV_COLOR_MAKE(255, 0, 0);
    myButtonStylePR.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
    myButtonStylePR.body.radius = 0;
    myButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);

    myButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(myButton, 0); //set button is to 0
    lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
    lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); //set the relesed style
    lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); //set the pressed style
    lv_obj_set_size(myButton, 200, 50); //set the button size
    lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); //set the position to top mid

    myButtonLabel = lv_label_create(myButton, NULL); //create label and puts it inside of the button
    lv_label_set_text(myButtonLabel, "Click the Button"); //sets label text

    myLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
    lv_label_set_text(myLabel, "Button has not been clicked yet"); //sets label text
    lv_obj_align(myLabel, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0); //set the position to center
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
  tareMotors();
  while(true){
  		//Tank Mode
  		setDriveTrain(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
      controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

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
