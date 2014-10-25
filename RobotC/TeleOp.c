#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     irSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Motor,  motorA,          flag,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     backRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontRight,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     frontLeft,     tmotorTetrix, openLoop, encoder)

#include "JoystickDriverChanges.c"

int joystickLeftX;
int joystickRightX;
int joystickLeftY;
int joystickRightY;
int deadZone = 10;

// 1 is the right joystick
// 2 is the left joystick

/* inputManager reads input from both controllers and sets the values of
	 corresponding variables

	 Controller 1:
	    Left Joystick (X and Y): Robot Movement (Front, Back, Left Strafe, Right Strafe)
	    Right Joystick (X) : Robot Movement (Turn)

	 Controller 2:
*/

int checkDeadZone(int joystickValue)
{
	if (joystickValue > deadZone || joystickValue < -deadZone)
	{
		return joystickValue;
	}
	else
	{
		return 0;
	}
}

void inputManager()
{
	while(true)
	{
			joystickRightY = checkDeadZone(joystick.joy1_y1);
			joystickLeftY = checkDeadZone(joystick.joy1_y2);
			joystickRightX = checkDeadZone(joystick.joy1_x1);
			joystickLeftX = checkDeadZone(joystick.joy1_x2);
	}
}


// uses the joystick values to drive the wheels
// can drive in both "mecanum mode" and "tank mode"
task Drive()
{
	// mecanum driving
	// 242 could be more precise
	// think about implementing dampening and quadratic shifting
	motor[frontLeft] = ((joystickLeftY + joystickRightX + joystickLeftX) / 343) * 100;
	motor[backLeft] = ((joystickLeftY - joystickRightX - joystickLeftX) / 343) * 100;
	motor[frontRight] = ((joystickLeftY + joystickRightX - joystickLeftX) / 343) * 100;
	motor[backRight] = ((joystickLeftY - joystickRightX + joystickLeftX) / 343) * 100;

	// tank driving (emergency case);
	/*
	motor[frontLeft] = joystickRightY;
	motor[backLeft] = joystickRightY;
	motor[frontRight] = joystickLeftY;
	motor[backRight] = joystickLeftY;
	*/

}

task main()
{
	inputManager();
	StartTask(Drive);
}
