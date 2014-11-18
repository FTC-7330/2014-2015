#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)

task main()
{
drive(x);
if (IR sensor reads that IR is ahead)
	approach IR;

	else
		turn(-x);
		drive(x);
		turn(x);
		drive(x);

		if (IR sensor reads that IR is right)
			approach IR;

		else
			drive(x);
			turn(x);
			drive(x);
			approach IR


}

//approach IR

while(IR != straight)
	turn(some direction)

driveNoWait;
while(touchSensor != down) {}
stop;
drive(-x)
