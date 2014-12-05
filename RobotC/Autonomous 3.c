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
	int x = 23;
	initializeRobot();
	drive(x);

	if (irSeeker.acValues[1] > 10 && irSeeker.acValues[2] > 10)
		approachIR();
	else
  {
		turn(-x);
		drive(x);
		turn(x);
		drive(x);
  }

	if (irSeeker.acValues[3] > 10 && irSeeker.acValues[4] > 10)
		approachIR();

	else
  {
		drive(x);
		turn(x);
		drive(x);
		approachIR();
  }

}
