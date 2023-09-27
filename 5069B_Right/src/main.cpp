    /*----------------------------------------------------------------------------*/
    /*                                                                            */
    /*    Module:       main.cpp                                                  */
    /*    Author:       Arjun Rishi, Patrick Stolinski                            */
    /*    Created:      Sat Jan 09 2020                                           */
    /*                                                                            */
    /*----------------------------------------------------------------------------*/

    // ---- START VEXCODE CONFIGURED DEVICES ----
    // Robot Configuration:
    // [Name]               [Type]        [Port(s)]
    // Controller1          controller                    
    // leftIntakeMotor      motor         3               
    // rightIntakeMotor     motor         4               
    // intakeSpinner        motor         5               
    // ejectionSpinner      motor         6               
    // middleSpinner        motor         7               
    // outtakeSpinner       motor         8               
    // driveTrainLeft       motor         1               
    // driveTrainRight      motor         2               
    // VisionSensor         vision        9               
    // VisionTwo            vision        10              
    // ---- END VEXCODE CONFIGURED DEVICES ----

    #include "vex.h"

    using namespace vex;

    competition Competition;
    vision::signature SIG_BLUE (1, -2913, -1607, -2260, 7351, 11879, 9615, 1.000, 0);
    vision::signature SIG_RED (2, 6127, 8429, 7278, -511, 505, -3, 2.200, 0);
    vision::signature SIG_GREEN (3, -5851, -5359, -5605, -5923, -5481, -5702, 6.000, 0);
    vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 3.000, 0);
    vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 3.000, 0);
    vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 2.500, 0);
    vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 2.500, 0);
    vex::vision vision1 ( vex::PORT1, 50, SIG_BLUE, SIG_RED, SIG_GREEN, SIG_4, SIG_5, SIG_6, SIG_7 );
    int centerFOV = 158;
    int offset = 10;
    int rollerSpeed = 70;
    int intakeSpeed = 70;
    int driveSpeed = 75;
    int shifter = 1;
        //if we are blue, set to 1, if we are red, set to two
    int blueOrRed = 0;
    bool origComplete = false;

    void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
    void forwardIntake() {
      leftIntakeMotor.spin(directionType :: fwd, intakeSpeed , velocityUnits :: pct);
      rightIntakeMotor.spin(directionType :: fwd, intakeSpeed , velocityUnits :: pct);
      waitUntil(!Controller1.ButtonL1.pressing());
      leftIntakeMotor.stop();
      rightIntakeMotor.stop();
    }
    void reverseIntake() {
      leftIntakeMotor.spin(directionType :: rev, intakeSpeed , velocityUnits :: pct);
      rightIntakeMotor.spin(directionType :: rev, intakeSpeed , velocityUnits :: pct);
      waitUntil(!Controller1.ButtonR1.pressing());
      leftIntakeMotor.stop();
      rightIntakeMotor.stop();
    }
    void bringBallUp(){
      intakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
      ejectionSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
      middleSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
      outtakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
      waitUntil(!Controller1.ButtonL2.pressing());
      intakeSpinner.stop();
      ejectionSpinner.stop();
      middleSpinner.stop();
      outtakeSpinner.stop();
    }
    void bringBallDown(){
      intakeSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
      ejectionSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
      middleSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
      outtakeSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
      waitUntil(!Controller1.ButtonR2.pressing());
      intakeSpinner.stop();
      ejectionSpinner.stop();
      middleSpinner.stop();
      outtakeSpinner.stop();
    }
    void reverseTopSpinner(){
      outtakeSpinner.spin(directionType :: rev, rollerSpeed , velocityUnits :: pct);
      waitUntil(!Controller1.ButtonY.pressing());
      outtakeSpinner.stop();
    }
    void shiftUp(){
      if(shifter <=4){
        shifter++;
      }
      if(shifter == 1){
        driveSpeed = 25;
      }
      if(shifter == 2){
        driveSpeed = 50;
      }
      if(shifter == 3){
        driveSpeed = 75;
      }
      if(shifter == 4){
        driveSpeed = 100;
      }
    }
    void shiftDown(){
      if(shifter >= 1){
        shifter--;
      }
      if(shifter == 1){
        driveSpeed = 25;
      }
      if(shifter == 2){
        driveSpeed = 50;
      }
      if(shifter == 3){
        driveSpeed = 75;
      }
      if(shifter == 4){
        driveSpeed = 100;
      }
    }
    void ejection(){
      ejectionSpinner.spin(directionType :: rev, 70 , velocityUnits :: pct);
      waitUntil(!Controller1.ButtonB.pressing());
      ejectionSpinner.spin(directionType :: fwd, 70 , velocityUnits :: pct);
    }
    void cycleProgram(){
      if(blueOrRed == 1){
        while(Controller1.ButtonUp.pressing()){
      intakeSpinner.spin(directionType :: fwd, 70 , velocityUnits :: pct);
      ejectionSpinner.spin(directionType :: fwd, 70 , velocityUnits :: pct);
      middleSpinner.spin(directionType :: fwd, 70 , velocityUnits :: pct);
      outtakeSpinner.spin(directionType :: fwd, 70 , velocityUnits :: pct);
      VisionSensor.takeSnapshot(SIG_RED);
      if(VisionSensor.largestObject.exists){
        intakeSpinner.stop();
        middleSpinner.stop();
        outtakeSpinner.stop();
        while(VisionSensor.largestObject.exists && Controller1.ButtonUp.pressing()){
          ejectionSpinner.spin(directionType :: rev, 50 , velocityUnits :: pct);
        }
        ejectionSpinner.stop();
        }
      }
      intakeSpinner.stop();
      ejectionSpinner.stop();
      middleSpinner.stop();
      outtakeSpinner.stop();
      }else if(blueOrRed == 2){
        while(Controller1.ButtonUp.pressing()){
      intakeSpinner.spin(directionType :: fwd, 70 , velocityUnits :: pct);
      ejectionSpinner.spin(directionType :: fwd, 70 , velocityUnits :: pct);
      middleSpinner.spin(directionType :: fwd, 70 , velocityUnits :: pct);
      outtakeSpinner.spin(directionType :: fwd, 70 , velocityUnits :: pct);
      VisionSensor.takeSnapshot(SIG_BLUE);
      if(VisionSensor.largestObject.exists){
        intakeSpinner.stop();
        middleSpinner.stop();
        outtakeSpinner.stop();
        while(VisionSensor.largestObject.exists && Controller1.ButtonUp.pressing()){
          ejectionSpinner.spin(directionType :: rev, 50 , velocityUnits :: pct);
        }
        ejectionSpinner.stop();
        }
    }
      }
    }

    void usercontrol(void) {
      vexcodeInit();
      while (true) {
      if(!origComplete){
        VisionSensor.takeSnapshot(SIG_BLUE);
        if(VisionSensor.largestObject.exists){
          Brain.Screen.print("TEAM 5069B IS BLUE");
          blueOrRed = 1;
          origComplete = true;
        }
        VisionSensor.takeSnapshot(SIG_RED);
        if(VisionSensor.largestObject.exists){
          Brain.Screen.print("TEAM 5069B IS RED");
          blueOrRed = 2;
          origComplete = true;
        }
      }
      int leftJoystick = Controller1.Axis3.position(percent);
      int rightJoystick = Controller1.Axis2.position(percent);
      if(leftJoystick < driveSpeed){
        driveTrainLeft.setVelocity(Controller1.Axis3.position(), percent);
      }else if(leftJoystick > driveSpeed){
        driveTrainLeft.setVelocity(driveSpeed, percent);
      }
      if(rightJoystick < driveSpeed){
        driveTrainRight.setVelocity(Controller1.Axis2.position(), percent);
      }else if(rightJoystick > driveSpeed){
        driveTrainRight.setVelocity(driveSpeed, percent);
      }
      driveTrainLeft.spin(forward);
      driveTrainRight.spin(forward);

      Controller1.ButtonL1.pressed(forwardIntake);
      Controller1.ButtonR1.pressed(reverseIntake);
      Controller1.ButtonL2.pressed(bringBallUp);
      Controller1.ButtonR2.pressed(bringBallDown);
      Controller1.ButtonY.pressed(reverseTopSpinner);
      Controller1.ButtonB.pressed(ejection);
      Controller1.ButtonX.pressed(shiftUp);
      Controller1.ButtonY.pressed(shiftDown);
      Controller1.ButtonUp.pressed(cycleProgram);

      leftIntakeMotor.setStopping(hold);
      rightIntakeMotor.setStopping(hold);
      intakeSpinner.setStopping(hold);
      ejectionSpinner.setStopping(hold);
      middleSpinner.setStopping(hold);
      outtakeSpinner.setStopping(hold);
    }
    }
    //we blue in this one too:)
    //follow the damn ball and score it
    //like the name don't ya? *uwu*
    void autonomous(void) {
      vexcodeInit();
        bool follow = false;
        bool follow1 = false;
        Brain.Screen.clearScreen();
        Brain.Screen.print("Autonomous");
    //define blue/ red
            if(!origComplete)
                            {
        VisionSensor.takeSnapshot(SIG_BLUE);
        if(VisionSensor.largestObject.exists)
          {
          //Brain.Screen.print("TEAM 5069B IS BLUE");
          blueOrRed = 1;
          origComplete = true;
          }
        VisionSensor.takeSnapshot(SIG_RED);
        if(VisionSensor.largestObject.exists){
          //Brain.Screen.print("TEAM 5069B IS RED");
          blueOrRed = 2;
          origComplete = true;
                              }
      }
    
    //going forward and turning
    driveTrainLeft.spin(directionType :: fwd, 75, velocityUnits :: pct);
    driveTrainRight.spin(directionType :: fwd, 75, velocityUnits :: pct);
    wait(4000, msec);
    driveTrainLeft.spin(directionType :: fwd, 75, velocityUnits :: pct);
    driveTrainRight.spin(directionType :: rev, 75, velocityUnits :: pct);
    wait( 1500, msec);
    //vision sensor stuff absolutely nothing to see here:)
  if(blueOrRed == 1){
      VisionTwo.takeSnapshot(SIG_BLUE);
    }else if(blueOrRed == 2){
      VisionTwo.takeSnapshot(SIG_RED);
    }
    while(VisionTwo.largestObject.exists)
      {
      if(blueOrRed == 1){
      VisionTwo.takeSnapshot(SIG_BLUE);
    }else if(blueOrRed == 2){
      VisionTwo.takeSnapshot(SIG_RED);
    }
      //takes a shot to scan for blue, if it finds it go forward to it with two if statements
      if(VisionTwo.largestObject.exists && VisionTwo.largestObject.centerX > centerFOV + offset)
      {
        driveTrainRight.spin(directionType :: rev, 20 , velocityUnits :: pct);
        driveTrainLeft.spin(directionType :: fwd, 20 , velocityUnits :: pct);
        leftIntakeMotor.setVelocity(65, percent);
        follow = true;
        wait(26, msec);//gotta wait for dem wheels to catch up so that the while loop does not activate all of a sudden
      }

      else if(VisionTwo.largestObject.exists && VisionTwo.largestObject.centerX < centerFOV - offset){
        driveTrainRight.spin(directionType :: fwd, 20 , velocityUnits :: pct);
        driveTrainLeft.spin(directionType :: rev, 20 , velocityUnits :: pct);
        follow1 = true;
    wait(26, msec);
    }
      }
      //brings the robot towards the ball with the intakes spinning
        driveTrainRight.spin(directionType :: fwd, 60 , velocityUnits :: pct);
        driveTrainLeft.spin(directionType :: fwd, 60 , velocityUnits :: pct);
        leftIntakeMotor.spin(directionType :: fwd, 75 , velocityUnits :: pct);
        rightIntakeMotor.spin(directionType :: fwd, 75 , velocityUnits :: pct);
        intakeSpinner.spin(directionType :: fwd, 75 , velocityUnits :: pct);
        ejectionSpinner.spin(directionType :: fwd, 75 , velocityUnits :: pct);
        middleSpinner.spin(directionType :: fwd, 75 , velocityUnits :: pct);
        wait(4000, msec);
        driveTrainRight.stop();
        driveTrainLeft.stop();
        leftIntakeMotor.stop();
        rightIntakeMotor.stop();
        intakeSpinner.stop();
        ejectionSpinner.stop();
        middleSpinner.stop();
        driveTrainRight.spin(directionType :: rev, 60 , velocityUnits :: pct);
        driveTrainLeft.spin(directionType :: rev, 60 , velocityUnits :: pct);
        wait(1000, msec);
        driveTrainRight.stop();
        driveTrainLeft.stop();
    //scans for the green on th tower:)
    VisionTwo.takeSnapshot(SIG_GREEN);
    while(VisionTwo.largestObject.exists)
      {
        VisionTwo.takeSnapshot(SIG_GREEN);
          if(VisionTwo.largestObject.exists && VisionTwo.largestObject.centerX > centerFOV + offset)
      {
        driveTrainRight.spin(directionType :: rev, 20 , velocityUnits :: pct);
        driveTrainLeft.spin(directionType :: fwd, 20 , velocityUnits :: pct);
        leftIntakeMotor.setVelocity(65, percent);
        follow = true;
        wait(26, msec);//gotta wait for dem wheels to catch up so that the while loop does not activate all of a sudden
      }//these two if and else if align us with the green flag (i moved it up)

      else if(VisionTwo.largestObject.exists && VisionTwo.largestObject.centerX < centerFOV - offset){
        driveTrainRight.spin(directionType :: fwd, 20 , velocityUnits :: pct);
        driveTrainLeft.spin(directionType :: rev, 20 , velocityUnits :: pct);
        follow1 = true;
      wait(26, msec);
    }
      }
      //moving the bot to the goal because we are aligned
      driveTrainRight.spin(directionType :: fwd, 50 , velocityUnits :: pct);
      driveTrainLeft.spin(directionType :: fwd, 50 , velocityUnits :: pct);
      wait(1500, msec);
      driveTrainLeft.stop();
      driveTrainRight.stop();
    //motors into action
    leftIntakeMotor.spin(directionType :: fwd, intakeSpeed , velocityUnits :: pct);
    rightIntakeMotor.spin(directionType :: fwd, intakeSpeed , velocityUnits :: pct);
    intakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
    ejectionSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
    middleSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
    outtakeSpinner.spin(directionType :: fwd, rollerSpeed , velocityUnits :: pct);
    wait(2000, msec);
    leftIntakeMotor.stop();
    rightIntakeMotor.stop();
    intakeSpinner.stop();
    ejectionSpinner.stop();
    middleSpinner.stop();
    outtakeSpinner.stop();
    //turn the bot around for the middle tower possibly probably not enough experimentation for this :(
    driveTrainRight.spin(directionType :: rev, 20 , velocityUnits :: pct);
    driveTrainLeft.spin(directionType :: rev, 20 , velocityUnits :: pct);
    wait(1500, msec);
    driveTrainRight.spin(directionType :: rev, 20 , velocityUnits :: pct);
    driveTrainLeft.spin(directionType :: fwd, 20 , velocityUnits :: pct);
    wait(750, msec);
    driveTrainRight.spin(directionType :: fwd, 20 , velocityUnits :: pct);
    driveTrainLeft.spin(directionType :: fwd, 20 , velocityUnits :: pct);
    wait(1000, msec);
    driveTrainLeft.stop();
    driveTrainRight.stop();
      //this is where we could repeat but its very risky
  // while(true)
  //   {
  //     VisionTwo.takeSnapshot(SIG_GREEN);
  //       if(VisionTwo.largestObject.centerX > centerFOV + offset)
  //       {
  //         driveTrainRight.spin(directionType :: rev, 20 , velocityUnits :: pct);
  //         driveTrainLeft.spin(directionType :: fwd, 20 , velocityUnits :: pct);
  //         if(VisionTwo.largestObject.height > 500)
  //         {
  //          //stop the drivetrain here its aligned all good
  //           //out take motor activator pls uwu (yes a computer can feel emoshun)
  //         }
  //       }
  // //end of a journey :) hats off to all the people inside the team.GREAT JOB.
  //   }
  // }else if(blueOrRed == 2){

    //
  }
  int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
