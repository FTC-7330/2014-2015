
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
float targetHeading;

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

task updateHeading()
{
	while(true)
	{
		currentVelocity = SensorValue[gyro] - initial; // gets the new sensor reading
		degHeading = degHeading + ((currentVelocity) * (time1[T1] - lastTime) * .001); // modifies the header
		lastTime = time1[T1]; // sets the last time for the next reading

		if(time1[T1] > 30000)
		{
			time1[T1] = 0;
			lastTime = 0;
		}

		radHeading = degHeading / 180 * PI; // the heading expressed in radians
		wait1Msec(5);
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

// This takes in power and degree Distance and returns it as turn power
int turnPower(float degDistance, int maxPower)
{
	return (floatMin(degDistance, 15.0) / 15.0) * (maxPower - 10) + 10;
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
//!!!!!!!!!!!!!!!!!!!!!!**********************************LEFT IS NEGATIVE*****************************!!!!!!!!!!!!!!!!!!
void turn(float degrees, int power)// power is always positive. degrees is positive or negative
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
				tankDrive(power, -power); //drive left at -power and right at power
			}
			else // Right turn
			{
				//drive(0.02, -power, power);
				tankDrive(-power, power); // drive left at power and right at -power
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



// Displays value of the IR sensor, the right and left encoders, and the sonar sensor
task display()
{
    while (true)
    {
    	//Displays information about encoders and IR and sonar sensors
			int leftEncoder = nMotorEncoder[backLeft];
			int rightEncoder = nMotorEncoder[backRight];

			nxtDisplayString(1,"back left: %d", nMotorEncoder[backLeft]);
			nxtDisplayString(2, "back right %d", nMotorEncoder[backRight]);
		  nxtDisplayString(3,"front left: %d", nMotorEncoder[frontLeft]);
			nxtDisplayString(4, "front right %d", nMotorEncoder[frontRight]);
	  }
}


int readIR()
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

task printHeading()
{
	while(true)
	{
		writeDebugStreamLine("Time: %d", time1[T1]);
		writeDebugStreamLine("Last Time: %d",  lastTime, time1[T1]);
		writeDebugStreamLine("Deg Heading: %d", degHeading);
		writeDebugStreamLine("Target Heading: %d", targetHeading);
		writeDebugStreamLine("Initial: %d", initial);
		writeDebugStreamLine("Angular Velocity: %d", SensorValue[gyro] - initial);
		writeDebugStreamLine("----------------------------");
		wait1Msec(200);
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

// Initializes the Robot at the beginning of the match.
//!!!!!!!!!!!!!!!!!!!***********************needs to be called in order for robot to work********************************!!!!!!!!!!!!
void initializeRobot()
{
	ClearTimer(T1);
	int sum = 0;
	for (int i = 0; i < 100; i++) {
		sum += SensorValue[gyro];
		wait1Msec(1);
	}
	initial = sum / 100;
	startTask(updateHeading);
	//initSensor(&irSeeker, S1);
	//return;
	//gyro initialize?
}
