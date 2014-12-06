#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S2,     touchSensor,            sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)

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
		drive(x);
		turn(-90, 30);
		drive(x);
		turn(60, 30);
		drive(x);
		turn(90);
		approachIR();
		//lift thing (credit to brian)
		//drop the balls in the center goal
	}
	else // beacon position 1
	{
		drive(x);
		turn(-90, 30);
		drive(x);
		turn(60, 30);
		drive(x);
		turn(30, 30);
		drive(x);
		turn(90, 30);
		approachIR();
		//lift thing (credit to brian)
		//drop the balls in the center goal
	}
}
