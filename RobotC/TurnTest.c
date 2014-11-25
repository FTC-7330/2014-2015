#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S3,     irSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
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
	//startTask(printHeading);
	//Drive(15, 30, 30);
	Turn(45, 30);
	//Turn(35, 50);
	//Turn(-360, 90);
}
