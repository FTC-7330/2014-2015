#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ultrasonic,     sensorSONAR)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     winchMotor,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     hookMotor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     collectionMotor, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    leftGate,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    rightGate,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    bucket,               tServoStandard)

#include "2014 Autonomous Functions.h"
#include "JoystickDriver.c"

int position;

task main()
{
	//waitForStart();
	initializeRobot();
	int position = findPosition();
	nxtDisplayString(1,"position: %d", position);
	nxtDisplayString(2, "sensor: %d", sensorValue(ultrasonic));

	if (position == 1)
	{
		drive(-400, -50, -50);
		turn(90, 40);
		drive(-2800, -50, -50);
		turn(-90, 40);
		drive(-3800, -50, -50)
		turn(-90, 40);
		drive(-3800, -80, -80);
	}
	else if (position == 2)
	{
		drive(-2850, -50, -50);
		turn(40, 40);
		drive(-3000, -80, -80);
	}
	else
	{
 		drive(-2000, -50, -50);
 		wait1Msec(200);
 		turn(90, 40);
 		drive(-2100, -50, -50);
 		wait1Msec(200);
 		turn(-90, 40);
 		wait1Msec(200;
 		drive(-4000, -80, -80);
		wait1Msec(200);
	}
}
