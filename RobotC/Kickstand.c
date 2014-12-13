#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)

#include "2014 Autonomous Functions.h"

task main()
{
	if (ir == 1)
	{
		Drive(-x);
		Turn(-90, 40);
		Drive(-x);
		Turn(90, 40);
		Drive(-x)
		Turn(90, 40);
		Drive(-x, 80, 80);
		Drive(6, 80, 80);
		Drive(-10, 80, 80);
		Drive(6, 80, 80);
		Drive(-10, 80, 80);
	}
	if (ir == 2)
	{
		Drive(-x);
		Turn(-45, 40);
		Drive(-x, 80, 80);
		Drive(6, 80, 80);
		Drive(-10, 80, 80);
		Drive(6, 80, 80);
		Drive(-10, 80, 80);
	}
	if (ir == 3)
	{
 		Drive(-x);
 		Turn(-90, 40);
 		Drive(-x);
 		Turn(90, 40);
 		Drive(-x, 80, 80);
 		Drive(6, 80, 80);
		Drive(-10, 80, 80);
		Drive(6, 80, 80);
		Drive(-10, 80, 80);
	}
}
