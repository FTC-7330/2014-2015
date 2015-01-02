#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     collectionMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     camMotor,      tmotorTetrix, openLoop)

#include "2014 Autonomous Functions.h"

task main()
{
	int beaconPosition = getBeaconPosition();
	if(beaconPosition == 3)
	{
		approachIR();
		//lift thing (credit to brian)
		//drop the balls in the center goal
	}
	else if(beaconPosition == 2)
	{
		drive(18, 30, 30);
		turn(-60, 30);
		drive(19, 30, 30);
		turn(120, 30);
		approachIR();
		//lift thing (credit to brian)
		//drop the balls in the center goal
	}
	else // beacon position 1
	{
		drive(18, 30, 30);
		turn(-60, 30);
		drive(38, 30, 30);
		turn(60, 30);
		drive(14, 30, 30);
		turn(90, 30);
		approachIR();
		//lift thing (credit to brian)
		//drop the balls in the center goal
	}
}
