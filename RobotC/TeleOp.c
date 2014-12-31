#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     irSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,          pinMotor,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     collectionMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     camMotor,      tmotorTetrix, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriverChanges.c"

#define BUTTON_X 1
#define BUTTON_Y 4
#define BUTTON_A 2
#define BUTTON_B 3
#define LEFT_BUTTON 5
#define RIGHT_BUTTON 6
#define BACK_BUTTON 9
#define START_BUTTON 10
#define TOP_HAT_UP 0
#define TOP_HAT_DOWN 4

int joystickLeftX;
int joystickRightX;
int joystickLeftY;
int joystickRightY;
int scaledLeftX;
int scaledRightX;
int scaledLeftY;
int scaledRightY;

bool isMecanum = true;
bool isCollectorRunning = false;
bool isShooterRunning = true;
bool isCamUp = false;


bool isTurbo;
int collectionPower = 70;
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

int scaleJoystickValues(int joystickValue)
{
	if(joystickValue>0)
	{
		return (int)((joystickValue*joystickValue)*.0062);
	}
	else
	{
		return (int)(-(joystickValue*joystickValue)*.0062);
	}
}
void inputManager()
{

	bool startJoyONEIsPressed = false;
	bool startJoyONEWasPressed = false;
	bool startJoyTWOIsPressed = false;
	bool startJoyTWOWasPressed = false;
	bool lbJoyTWOWasPressed = false;
	bool lbJoyTWOIsPressed = false;
	bool rbJoyTWOIsPressed = false;
	bool rbJoyTWOWasPressed = false;


	while(true)
	{
			getJoystickSettings(joystick);

			//Joystick 1 Booleans
			startJoyONEIsPressed = (joy1Btn(START_BUTTON)==1);

			//Joystick 2 Booleans
			rbJoyTWOIsPressed = (joy2Btn(RIGHT_BUTTON)==1);
			startJoyTWOIsPressed = (joy2Btn(START_BUTTON)==1);
			isTurbo = (joy2Btn(LEFT_BUTTON)==1);

			if(startJoyONEIsPressed&&!startJoyONEWasPressed)
			{
				isMecanum = !isMecanum;
			}

			if(startJoyTWOIsPressed&&!startJoyTWOWasPressed)
			{
				isCollectorRunning = !isCollectorRunning;
			}

			if((lbJoyTWOIsPressed&&!lbJoyTWOWasPressed)&&(rbJoyTWOIsPressed&&!rbJoyTWOWasPressed))
			{
				isShooterRunning = !isShooterRunning;
			}

			if(joy1Btn(TOP_HAT_UP)==1)
			{
				isCamUp = true;
			}
			else if(joy1Btn(TOP_HAT_DOWN)==1)
			{
				isCamUp = false;
			}


			joystickRightY = checkDeadZone(-joystick.joy1_y2);
			joystickLeftY = checkDeadZone(joystick.joy1_y1);
			joystickRightX = checkDeadZone(-joystick.joy1_x2);
			joystickLeftX = checkDeadZone(joystick.joy1_x1);

			scaledRightY = scaleJoystickValues(joystickRightY);
			scaledLeftY = scaleJoystickValues(joystickLeftY);
			scaledRightX = scaleJoystickValues(joystickRightX);
			scaledLeftX = scaleJoystickValues(joystickLeftX);

			//joystickRightY = checkDeadZone(-joystick.joy1_y2);
			// joystickLeftY = checkDeadZone(-joystick.joy1_y1);
			// joystickRightX = checkDeadZone(joystick.joy1_x2);
			// joystickLeftX = checkDeadZone(joystick.joy1_x1);

			startJoyONEWasPressed = startJoyONEIsPressed;
			startJoyTWOWasPressed = startJoyTWOIsPressed;
			rbJoyTWOWasPressed = rbJoyTWOIsPressed;
			lbJoyTWOWasPressed = lbJoyTWOIsPressed;
	}
}


// uses the joystick values to drive the wheels
// can drive in both "mecanum mode" and "tank mode"
task Drive()
{
	// mecanum driving
	// 242 could be more precise
	// think about implementing dampening and quadratic shifting
	while(true)
	{
		if(isMecanum)
		{
			motor[frontLeft] = (scaledLeftY - scaledRightX + scaledLeftX);
			motor[backLeft] =  (scaledLeftY - scaledRightX - scaledLeftX);
			motor[frontRight] = (scaledLeftY + scaledRightX - scaledLeftX);
			motor[backRight] = (scaledLeftY + scaledRightX + scaledLeftX);

			// motor[frontLeft] = (joystickLeftY - joystickRightX + joystickLeftX)*100/127;
			// motor[backLeft] =  (joystickLeftY - joystickRightX - joystickLeftX)*100/127;
			// motor[frontRight] = (joystickLeftY + joystickRightX - joystickLeftX)*100/127;
			// motor[backRight] = (joystickLeftY + joystickRightX + joystickLeftX) *100/127;
		}
		else
		{
			motor[frontLeft] = joystickRightY;
			motor[backLeft] = joystickRightY;
			motor[frontRight] = joystickLeftY;
			motor[backRight] = joystickLeftY;
		}
		wait1Msec(10);
	}
}

task Collection()
{

	while(true)
	{

		if(joystick.joy2_TopHat == TOP_HAT_UP)
		{
			motor[motorA]= 100;
		}
		else if(joystick.joy2_TopHat == TOP_HAT_DOWN)
		{
			motor[motorA] = -100;
		}
		else
		{
			motor[motorA] = 0;
			bFloatDuringInactiveMotorPWM = false;
		}



		if(isCollectorRunning)
		{
			motor[collectionMotor] = 50;
		}
		else
		{
			motor[collectionMotor] = 0;
		}

		wait1Msec(10);
	}

}



/*task Display()
{
	while(true)
	{
		writeDebugStreamLine("isCamUp: %d", isCamUp);
		writeDebugStreamLine("Cam Motor Encoder: %d",  nMotorEncoder[camMotor]);
		wait1Msec(10);
	}
}*/

task main()
{
	startTask(Drive);
	startTask(Collection);
	//startTask(Display);
	inputManager();
}
