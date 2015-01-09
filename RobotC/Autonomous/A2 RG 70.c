#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     ultrasonic,     sensorSONAR)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     winchMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     hookMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     collectionMotor, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    leftGate,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    rightGate,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    bucket,               tServoStandard)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "2014 Autonomous Functions.h"

// distance from top of ramp to bottom: 58 inches
// distance from ramp to rolling goals: ~48 inches
// distance from ramp to centerpiece: 31 inches
// distance from end of ramp to wall: 23.75 inches

task main()
{
	 // waitForStart();
	 initializeRobot();
	 nmotorEncoder[hookMotor] = 0;
	 startTask(printHeading);

	 // drive off the ramp backwards towards the 60cm rolling goal
	 drive(-58, -20, -20);
	 drive(-54, -50, -50);

	 motor[pinMotor] = 40;
	 while(nMotorEncoder[pinMotor] < 60)
	 {
	 }
  	motor[pinMotor] = 0;

		// drive forward to secure the goal
		drive(1, 20, 20);
		wait1Msec(100);

/*	motor[liftingMotor] = 30;
		wait1Msec(500);
		motor[liftingMotor] = 0;
		wait1Msec(100);
		motor[ballReleaseMotor] = 30;
		wait1Msec(200);
		motor[ballReleaseMotor] = 0; */

		turn(90, 50);
		drive(-35, -50, -50);
		turn(90, 50);
		drive(-98, -50, -50);
		turn(-90, 50);
		drive(-10, -50, -50);

	 // detatch the cammotor
/*	motor[camMotor] = -10;
		wait1Msec(200);
		motor[camMotor] = 0; */

}
