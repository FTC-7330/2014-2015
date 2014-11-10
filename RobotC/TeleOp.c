#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     backRight,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeft,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     frontLeft,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     collectionMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     camMotor,      tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriverChanges.c"

#define BUTTON_X 1
#define BUTTON_Y 4
#define BUTTON_A 2
#define BUTTON_B 3
#define LEFT_BUTTON 5
#define RIGHT_BUTTON 6
#define START_BUTTON 10
#define TOP_HAT_UP 0
#define TOP_HAT_DOWN 4

int joystickLeftX;
int joystickRightX;
int joystickLeftY;
int joystickRightY;
bool aPressed;
bool bPressed;
int collectionPower = 40;
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
			getJoystickSettings(joystick);
			bPressed = (joy1Btn(BUTTON_B)==1);
			aPressed = (joy1Btn(BUTTON_A)==1);
			joystickRightY = checkDeadZone(joystick.joy1_y1);
			joystickLeftY = checkDeadZone(joystick.joy1_y2);
			joystickRightX = checkDeadZone(joystick.joy1_x1);
			joystickLeftX = checkDeadZone(joystick.joy1_x2);
	}
}


// uses the joystick values to drive the wheels
// can drive in both "mecanum mode" and "tank mode"
task drive()
{
	// mecanum driving
	// 242 could be more precise
	// think about implementing dampening and quadratic shifting
	while(true)
	{
		motor[frontLeft] = (joystickLeftY - joystickRightX + joystickLeftX)*100/250;
		motor[backLeft] =  (joystickLeftY - joystickRightX - joystickLeftX)*100/250;
		motor[frontRight] = (joystickLeftY + joystickRightX - joystickLeftX)*100/250;
		motor[backRight] = (joystickLeftY + joystickRightX + joystickLeftX) *100/250;
	}
	// tank driving (emergency case);
	/*
	motor[frontLeft] = joystickRightY;
	motor[backLeft] = joystickRightY;
	motor[frontRight] = joystickLeftY;
	motor[backRight] = joystickLeftY;
	*/

}

task collection()
{
	while(true)
	{
		if(aPressed)
		{
			motor[collectionMotor] = collectionPower;
		}
		else
		{
			motor[collectionMotor] = 0;
		}
		if(bPressed)
		{
			motor[camMotor] = 10;
		}
		else
		{
			motor[camMotor] = 0;
		}
	}

}

task main()
{
	StartTask(drive);
	StartTask(collection);
	inputManager();
}
