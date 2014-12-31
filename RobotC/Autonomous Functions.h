// Functions for Autonomous Methods
// - display
// - turn
// - drive
// - findPosition
// - initializeRobot

float initialVelocity;
float degHeading;
float radHeading;
float targetHeading;

long lastTime = 0; // time counter for heading method
int currentVelocity; // angular velocity calculated by heading method

// helper method for drive - waits for motors to reach encoder target
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

// updates variable currentHeading to reflect the current heading in degrees
task updateHeading()
{
	while(true)
	{
		currentVelocity = SensorValue[gyro] - initialVelocity;
		degHeading = degHeading + ((currentVelocity) * (time1[T1] - lastTime) * .001);
		lastTime = time1[T1];

		if(time1[T1] > 30000)
		{
			time1[T1] = 0;
			lastTime = 0;
		}

		radHeading = degHeading / 180 * PI;
		wait1Msec(5);
	}
}

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

// duplicate of min with floats
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

// reset encoder values and drives for the given distance at the given speed
// to drive backwards, both distance and speed should be negative
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

// helper method for turn that takes in the maximum power and the remaining distance and returns the
// current power
int turnPower(float degDistance, int maxPower)
{
	return (floatMin(degDistance, 15.0) / 15.0) * (maxPower - 10) + 10;
}

// helper method that sets the right and left motors
void tankDrive(int left, int right)
{
	motor[backRight] = right;
	motor[backLeft] = left;
	motor[frontRight] = right;
	motor[frontLeft] = left;
}

// pre: power must be greater than 15, power should always be positive and degrees should be positive
// or negative based on the desired direction
// ***** LEFT IS NEGATIVE *****
// turns the robot to the input angle at the input power
void turn(float degrees, int power)
{
	targetHeading = degHeading + degrees;

	while (abs(targetHeading - degHeading) > 2)
	{
		while (abs(targetHeading - degHeading) > 2)
		{
			power = turnPower(abs(targetHeading - degHeading), power);
			if (targetHeading - degHeading > 0) // left turn
			{
				//drive(0.02, power, -power);
				tankDrive(power, -power);
			}
			else // right turn
			{
				//drive(0.02, -power, power);
				tankDrive(-power, power);
			}
			wait10Msec(10);
		}
		//wait10Msec(10);
	}

	motor[backRight] = 0;
	motor[backLeft] = 0;
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
}



// displays variables for debugging
task display()
{
    while (true)
    {
			int leftEncoder = nMotorEncoder[backLeft];
			int rightEncoder = nMotorEncoder[backRight];

			nxtDisplayString(1,"back left: %d", nMotorEncoder[backLeft]);
			nxtDisplayString(2, "back right %d", nMotorEncoder[backRight]);
		  nxtDisplayString(3,"front left: %d", nMotorEncoder[frontLeft]);
			nxtDisplayString(4, "front right %d", nMotorEncoder[frontRight]);
	  }
}

// returns an integer that reperesents the position of the center structure determined
// based on the ultrasonic sensor
int findPosition()
{
	if (SensorValue[ultrasonic] < 220)
	{
		return 1;
	}
	else if (SensorValue[ultrasonic] < 420)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

// debugging method that prints information about the heading
task printHeading()
{
	while(true)
	{
		writeDebugStreamLine("Time: %d", time1[T1]);
		writeDebugStreamLine("Last Time: %d",  lastTime, time1[T1]);
		writeDebugStreamLine("Deg Heading: %d", degHeading);
		writeDebugStreamLine("Target Heading: %d", targetHeading);
		writeDebugStreamLine("initialVelocity: %d", initialVelocity);
		writeDebugStreamLine("Angular Velocity: %d", SensorValue[gyro] - initialVelocity);
		writeDebugStreamLine("----------------------------");
		wait1Msec(200);
	}
}
// debugging method that prints encoder values
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

// initializes the robot at the beginning of the match
// ***** needs to be called in order for robot to work *****
// calculates initial velocity from the gyro and starts updateHeading
void initializeRobot()
{
	ClearTimer(T1);

	int sum = 0;
	for (int i = 0; i < 100; i++) {
		sum += SensorValue[gyro];
		wait1Msec(1);
	}
	initialVelocity = sum / 100;

	startTask(updateHeading);
}
