#include "3rd Party Driver Library\include\hitechnic-irseeker-v2.h"
tHTIRS2 irSeeker;

// Functions for Autonomous Methods
// - display
// - turn
// - drive
// - driveArm
// - driveFailSafe

// right test value: 270
// left test value: 260
// right competition value: ????
// left competition value: ????


float degHeading;
float initial;
float radHeading;
long lastTime = 0;
int currentVelocity;

void waitForStop();
task updateHeading()
{
	while(true)
	{
		currentVelocity = SensorValue[gyro] - initial; // gets the new sensor reading
		degHeading = degHeading + ((currentVelocity) * (time1[T1] - lastTime) * .001); // modifies the header
		lastTime = time1[T1]; // sets the last time for the next reading
		radHeading = degHeading / 180 * PI; // the heading expressed in radians
		//wait1Msec(10); consider uncommenting this line
	}
}

//It takes in two values and returns the minimum
int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

//It takes in two values and returns the minimum
float floatMin(float a, float b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

// reset encoder values; drives for the distance given at the given speed;
//if runForever is true, drives forever
void drive(int distanceInches, int rightSpeed, int leftSpeed)
{
	int distanceTicks = (int)(distanceInches / 0.044879895);
	nMotorEncoder[backRight] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[frontRight] = 0;
	nMotorEncoder[frontLeft] = 0;

	nMotorEncoderTarget[backRight] = distanceTicks;
	nMotorEncoderTarget[backLeft] = distanceTicks;
	nMotorEncoderTarget[frontRight] = distanceTicks;
	nMotorEncoderTarget[frontLeft] = distanceTicks;

	motor[backRight] = rightSpeed;
	motor[backLeft] = leftSpeed;
	motor[frontRight] = rightSpeed;
	motor[frontLeft] = leftSpeed;

	waitForStop();

	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[backRight] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[frontRight] = 0;
}

// This takes in power and degree Distance and returns it as turn power
int turnPower(float degDistance, int maxPower) {
	return (floatMin(degDistance, 10) / 10.0) * (maxPower - 15) + 15;
}

void tankDrive(int left, int right)
{
	motor[backRight] = right;
	motor[backLeft] = left;
	motor[frontRight] = right;
	motor[frontLeft] = left;
}

// power must be greater than 15
// This method takes in an amount of degrees and power so it
// can turn the robot at the given angle with the given power
void turn(float degrees, int power)// power is always positive. degrees is positive or negative
{
	float targetHeading = degHeading + degrees;
	while (abs(targetHeading - degHeading) > .25)
	{
		power = turnPower(abs(targetHeading - degHeading), power);
		if (targetHeading - degHeading > 0) // left turn
		{
			//drive(0.02, power, -power);
			tankDrive(-power, power); //drive left at -power and right at power
		}
		else // Right turn
		{
			//drive(0.02, -power, power);
			tankDrive(power, -power); // drive left at power and right at -power
		}

	}
	motor[backRight] = 0;
	motor[backLeft] = 0;
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
}



// Displays value of the IR sensor, the right and left encoders, and the sonar sensor
task display()
{
    while (true)
    {
    	//Displays information about encoders and IR and sonar sensors
			int freftEncoder = nMotorEncoder[backLeft];
			int rightEncoder = nMotorEncoder[backRight];

			nxtDisplayString(1,"back left: %d", nMotorEncoder[backLeft]);
			nxtDisplayString(2, "back right %d", nMotorEncoder[backRight]);
		  nxtDisplayString(3,"front left: %d", nMotorEncoder[frontLeft]);
			nxtDisplayString(4, "front right %d", nMotorEncoder[frontRight]);
	  }
}

task printHeading()
{
	while(true)
	{
		writeDebugStreamLine("Time: %d", time1[T1]);
		writeDebugStreamLine("Last Time: %d",  lastTime, time1[T1]);
	}
}
// Prints the Endoder Values on the NXT.
task printEncoderValues()
{
	while(true)
	{
		writeDebugStreamLine("Back Left Encoder Value: %d",nMotorEncoder[backLeft]);
		writeDebugStreamLine("Back Right Encoder Value: %d",nMotorEncoder[backRight]);
		writeDebugStreamLine("Front Left Encoder Value: %d",nMotorEncoder[frontLeft]);
		writeDebugStreamLine("Front Right Encoder Value: %d",nMotorEncoder[frontRight]);
		writeDebugStreamLine("");
		wait1Msec(500);
	}
}
// Continues driving until encoders reach destination, then resets motor speed.
void waitForStop()
{
	while(nMotorRunState[backRight] != runStateIdle && nMotorRunState[backLeft] != runStateIdle
		&& nMotorRunState[frontRight] != runStateIdle && nMotorRunState[frontLeft] != runStateIdle)
	{
	}

	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
	motor[frontRight] = 0;
}
// Initializes the Robot at the beginning of the match.
//!!!!!!!!!!!!!!!!!!!***********************needs to be called in order for robot to work********************************!!!!!!!!!!!!
void initializeRobot()
{
	ClearTimer(T1);
	startTask(updateHeading);
	int sum = 0;
	for (int i = 0; i < 100; i++) {
		sum += SensorValue[gyro];
		wait1Msec(1);
	}
	initial = sum / 100;

	initSensor(&irSeeker, S1);
	//gyro initialize?
}

void approachIR()
{
	int leftSpeed = 30;
	int rightSpeed = 30;
	int speedDelta = 2;
	tankDrive(leftSpeed, -rightSpeed);

	while (irSeeker.acValues[1] < 20 || irSeeker.acValues[2] < 20 || abs(irSeeker.acValues[2] - irSeeker.acValues[1]) > 10) //Ruthie's while loop
	{
	}
	tankDrive(0, 0);

	while(false)
	{
		tankDrive(leftSpeed, rightSpeed);

		if((irSeeker.acValues[1]+15) < irSeeker.acValues[2]) //if 2 gets a higher signal, drive towards it
		{
			motor[frontRight] = rightSpeed - speedDelta;
			motor[backRight] = rightSpeed - speedDelta;
		}
		if((irSeeker.acValues[2]+15) < irSeeker.acValues[1]) //if 1 gets a higher signal, drive towards it
		{
			motor[frontLeft] = rightSpeed - speedDelta;
			motor[backLeft] = rightSpeed - speedDelta;
		}
		wait1Msec(10);
	}
	tankDrive(0, 0);
}
