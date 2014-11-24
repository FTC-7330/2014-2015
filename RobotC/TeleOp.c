#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S3,     irSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, reversed)
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
bool isMecanum = true;
bool isCollectorRunning = false;
bool isShooterRunning = true;
bool isCamUp = false;


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
			lbJoyTWOIsPressed = (joy2Btn(LEFT_BUTTON)==1);
			startJoyTWOIsPressed = (joy2Btn(START_BUTTON)==1);

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

			// joystickRightY = checkDeadZone(-joystick.joy1_y2);
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
			motor[frontLeft] = (joystickLeftY - joystickRightX + joystickLeftX)*100/127;
			motor[backLeft] =  (joystickLeftY - joystickRightX - joystickLeftX)*100/127;
			motor[frontRight] = (joystickLeftY + joystickRightX - joystickLeftX)*100/127;
			motor[backRight] = (joystickLeftY + joystickRightX + joystickLeftX) *100/127;

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
	}
}

task Collection()
{
	while(true)
	{
		if(joy2Btn(5)==1)
		{
			motor[camMotor] = 50;
			/*if(nMotorEncoder[camMotor] < 1440)
			{
				motor[camMotor] = 50;
			}
			else
			{
				 motor[camMotor] = 0;
			}*/
		}
		else if(joy2Btn(6)==1)
		{
			motor[camMotor] = -50;
			/*if(nMotorEncoder[camMotor] > 0)
			{
				motor[camMotor] = -50;
			}
			else
			{
				motor[camMotor] = 0;
			}*/
		}
		else
		{
			motor[camMotor] = 0;
		}

		if(isCollectorRunning)
		{
			motor[collectionMotor] = 50;
		}
		else
		{
			motor[collectionMotor] = 0;
		}
	}

}

task Display()
{
	while(true)
	{
		writeDebugStreamLine("isCamUp: %d", isCamUp);
		writeDebugStreamLine("Cam Motor Encoder: %d",  nMotorEncoder[camMotor]);
	}
}

task main()
{
	startTask(Drive);
	startTask(Collection);
	startTask(Display);
	inputManager();
}
