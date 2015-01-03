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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "2014 Autonomous Functions.h"

task main()
{
	initializeRobot();
	//while(true)
	//{
		//motor[backRight] = 90;
	//}
	//drive(20, 50, 50);
	//wait1Msec(200);
	//turn(90, 40);
	//wait1Msec(200);
	//drive(-10, -50, -50);
	//wait1Msec(200);
	//turn(-45, 40);
//	wait1Msec(200);
	//drive(10, 70, 70);

	for (int i = 0; i < 4; i++)
	{
		turn(90, 40);
		wait1Msec(200);
	}
}
