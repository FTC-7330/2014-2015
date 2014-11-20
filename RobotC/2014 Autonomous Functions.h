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
		if (time1[T1] > 30000) // this resets the timer after 30 seconds
		{
			clearTimer(T1);
			lastTime = 0;
		}
		radHeading = degHeading / 180 * PI; // the heading expressed in radians
		//wait1Msec(10); // lets other tasks run
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
int turnPower(float degDistance, int power) {
	return (min((degDistance), 10) / 10) * (power - 15) + 15;
}
// power must be greater than 15
// This method takes in an amount of degrees and power so it
// can turn the robot at the given angle with the given power
void turn(float degrees, int power)
{
	float targetHeading = degHeading + degrees;
	while (abs(targetHeading - degHeading) > .25)
	{
		power = turnPower(abs(targetHeading - degHeading), power);
		if (targetHeading - degHeading > 0) // left turn
		{
			//drive(0.02, power, -power);
			motor[backRight] = power;
			motor[backLeft] = -power;
			motor[frontRight] = power;
			motor[frontLeft] = -power;
		}
		else // Right turn
		{
			//drive(0.02, -power, power);
			motor[backRight] = -power;
			motor[backLeft] = power;
			motor[frontRight] = -power;
			motor[frontLeft] = power;
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
void initializeRobot()
{
	ClearTimer(T1);

	int sum = 0;
	for (int i = 0; i < 100; i++) {
		sum += SensorValue[gyro];
		wait1Msec(1);
	}
	initial = sum / 100;

	initSensor(&irSeeker, S1);
}

void approachIR()
{
	motor[frontRight] = -50;
	motor[frontLeft] = 50;
	motor[backRight] = -50;
	motor[backLeft] = 50;


	while (irSeeker.acValues[1] > 40 && irSeeker.acValues[2] > 40 && abs(irSeeker.acValues[2] - irSeeker.acValues[1]) > 20) //Ruthie's while loop
	{
	}

	motor[frontRight] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;

	int d;
	int p;
	int i;
	int rSpeed, lSpeed = 50;

	motor[frontRight] = rSpeed;
	motor[frontLeft] = lSpeed;
	motor[backRight] = rSpeed;
	motor[backLeft] = lSpeed;

	while (false) //condition needs to be if touchSensor returns True or False. Look up syntax later
	{
		d = irSeeker.dcValues[1] - irSeeker.dcValues[2];
		p = d;
		i += 0.01*d;
		rSpeed += 1*p + 2*i; //1 is a filler for constant k1, 2 is a filler for constant k2
		lSpeed -= 1*p +2*i;
		motor[frontRight] = rSpeed;
  	motor[frontLeft] = lSpeed;
		motor[backRight] = rSpeed;
		motor[backLeft] = lSpeed;
		wait1Msec(10);
	}
}
