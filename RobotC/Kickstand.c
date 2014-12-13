#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)

#include "2014 Autonomous Functions.h"

task main()
{
	intializeRobot();
	if (ir == 1)
	{
		drive(-20, -80, -80);
		turn(-90, 40);
		drive(-10, -80, -80);
		turn(90, 40);
		drive(-15, -80, -80)
		turn(90, 40);
		drive(-20, -80, -80);
		for(int i = 0; i < 3; i++)
		{
			drive(6, 80, 80);
			drive(-10, 80, 80);
		}
	}
	else if (ir == 2)
	{
		drive(-20, -80, -80);
		turn(45, 40);
		drive(-10, -80, -80);
		for(int i = 0; i < 3; i++)
		{
			drive(6, 80, 80);
			drive(-10, 80, 80);
		}
	}
	else
	{
 		drive(-20, -80, -80);
 		turn(-90, 40);
 		drive(-10, -80, -80);
 		turn(90, 40);
 		drive(-25, -80, -80);
		for(int i = 0; i < 3; i++)
		{
			drive(6, 80, 80);
			drive(-10, 80, 80);
		}
	}
}
