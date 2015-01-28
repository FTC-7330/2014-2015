#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ultrasonic,     sensorSONAR)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C2_1,     backRight,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     frontLeft,     tmotorTetrix, PIDControl, reversed, encoder)

#include "JoystickDriver.c"

void initializeRobot()
{
}
int checkDeadZone(int joystickValue)
{
	if (joystickValue > deadZone || joystickValue < -deadZone)
	{		return joystickValue;
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
	//Initializing when buttons are pressed.
	bool startJoyONEIsPressed = false;
	bool startJoyONEWasPressed = false;
	bool startJoyTWOIsPressed = false;
	bool startJoyTWOWasPressed = false;


	while(true)
	{
			getJoystickSettings(joystick);

			//Joystick 1 Booleans
			startJoyONEIsPressed = (joy1Btn(START_BUTTON)==1);

			//Joystick 2 Booleans
			startJoyTWOIsPressed = (joy2Btn(START_BUTTON)==1);
			isTurbo = (joy2Btn(LEFT_BUTTON)==1);


			//Toggle to tank drive (which doesn't work).
			if(startJoyONEIsPressed&&!startJoyONEWasPressed)
			{
				isMecanum = !isMecanum;
			}


			joystickRightY = checkDeadZone(-joystick.joy1_y2);
			joystickLeftY = checkDeadZone(joystick.joy1_y1);
			joystickRightX = checkDeadZone(-joystick.joy1_x2);
			joystickLeftX = checkDeadZone(joystick.joy1_x1);

			scaledRightY = scaleJoystickValues(joystickRightY);
			scaledLeftY = scaleJoystickValues(joystickLeftY);
			scaledRightX = scaleJoystickValues(joystickRightX);
			scaledLeftX = scaleJoystickValues(joystickLeftX);

			// joystickRightY = checkDeadZone(-joystick.joy1_y2);
			// joystickLeftY = checkDeadZone(-joystick.joy1_y1);
			// joystickRightX = checkDeadZone(joystick.joy1_x2);
			// joystickLeftX = checkDeadZone(joystick.joy1_x1);

			startJoyONEWasPressed = startJoyONEIsPressed;
			/*rbJoyONEWasPressed = rbJoyONEIsPressed;
			lbJoyONEWasPressed = lbJoyONEIsPressed;*/

			startJoyTWOWasPressed = startJoyTWOIsPressed;
			/*rbJoyTWOWasPressed = rbJoyTWOIsPressed;
			lbJoyTWOWasPressed = lbJoyTWOIsPressed;
			yJoyTWOWasPressed = yJoyTWOIsPressed;
			aJoyTWOWasPressed = aJoyTWOIsPressed;*/
			// wait1Msec(waitTime);
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
			motor[frontLeft] = joystickLeftY;
			motor[backLeft] = joystickLeftY;
			motor[frontRight] = joystickRightY;
			motor[backRight] = joystickRightY;
		}
		wait1Msec(waitTime);
	}
}
task main()
{
	initializeRobot();
  waitForStart();
  startTask(Drive);
  inputManager();
}
