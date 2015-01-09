#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     ultrasonic,     sensorSONAR)
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

// moves robot from high goal to kickstand
void goToKickstand()
{
	drive(500, 50, 50);
	turn(90, 50);
	drive(-1500, -70, -70);
	turn(-90, 70);
	drive(-3500, -70, -70);
	wait1Msec(4000);
}

task main()
{
	initializeRobot();
	int beaconPosition = findPosition();
	if (beaconPosition == 3)
	{
		drive(-500,-500,-50);
		wait1Msec(100);
		turn(90,50);
		drive(-500,-500,-50);
		wait1Msec(100);
		turn(-90,50);
		drive(-2500,-2500,-50);
		//goToKickstand();
	}
	else if (beaconPosition == 2)
	{
		drive(-1000, -50, -50);
		wait1Msec(100);
		turn(-45, 50);
		drive(-2800, -50, -50);
		wait1Msec(100);
		turn(88, 50);
		drive(-1000, -50, -50);
		wait1Msec(2000);
		//goToKickstand();
	}
	else //position 1
	{
		drive(-2500, -50, -50);
		//wait1Msec(100);
		turn(-90, 50);
		//wait1Msec(100);
		drive(-2800, -50, -50);
		//wait1Msec(100);
		turn(90, 50);
		//wait1Msec(100);
		drive(-3100, -50, -50);
		//wait1Msec(100);
		turn(90, 50);
		//change the last drive value depending on how close the robot should be to the high goal
		//drive(1000, -50, -50);
		wait1Msec(2000);
		goToKickstand();
	}
}
