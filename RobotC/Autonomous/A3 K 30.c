#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S3,     ultrasonic,     sensorSONAR)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     camMotor,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     collectionMotor, tmotorTetrix, openLoop, reversed)

#include "2014 Autonomous Functions.h"

task main()
{
	initializeRobot();
	int position = readPosition();

	if (position == 1)
	{
		drive(-20, -80, -80);
		turn(90, 40);
		drive(-10, -80, -80);
		turn(-90, 40);
		drive(-15, -80, -80)
		turn(-90, 40);
		drive(-20, -80, -80);

		for(int i = 0; i <3; i++)
		{
			drive(6, 80, 80);
			drive(-10, 80, 80);
		}
	}
	else if (position == 2)
	{
		drive(-20, -80, -80);
		turn(-45, 40);
		drive(-10, -80, -80);

		for(int i = 0; i <3; i++)
		{
			drive(6, 80, 80);
			drive(-10, 80, 80);
		}
	}
	else
	{
 		drive(-20, -80, -80);
 		turn(90, 40);
 		drive(-10, -80, -80);
 		turn(-90, 40);
 		drive(-25, -80, -80);

 		for(int i = 0; i <3; i++)
		{
			drive(6, 80, 80);
			drive(-10, 80, 80);
		}
	}
}
