#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     backRight,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeft,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontRight,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     frontLeft,     tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    gripper,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)

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
int lastTime = 0;

void waitForStop();
void updateHeading()
{
	int currentVelocity = SensorValue[gyro] - initial; // gets the new sensor reading
	degHeading += (currentVelocity) * (time1[T1] - lastTime) * .001; // modifies the header
	lastTime = time1[T1]; // sets the last time for the next reading
	if (time1[T1] > 30000) // this resets the timer after 30 seconds
	{
		clearTimer(T1);
		lastTime = 0;
	}
	radHeading = degHeading / 180 * PI; // the heading expressed in radians
	wait1Msec(10); // lets other tasks run
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

// reset encoder values; drives for the distance given at the given speed;
//if runForever is true, drives forever
void drive(int distanceInches, int rightSpeed, int leftSpeed, bool runForever)
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

	if (!runForever) //stops when target is reached.
	{
		waitForStop();
	}

	nMotorEncoder[backRight] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[frontRight] = 0;
	nMotorEncoder[frontLeft] = 0;
}

int turnPower(float degDistance) {
	return (min((degDistance), 10) / 10) * 85 + 15;
}

void turn(float degrees, int power)
{
	float targetHeading = degHeading + degrees;
	while (abs(targetHeading - degHeading) > .25)
	{
		updateHeading();
		power = turnPower(abs(targetHeading - degHeading));
		if (targetHeading - degHeading > 0) // left turn
		{
			drive(0.02, power, -power, false);
		}
		else // right turn
		{
			drive(0.02, -power, power, false);
		}

	}
	motor[backRight] = 0;
	motor[backLeft] = 0;
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
}



// displays value of the IR sensor, the right and left encoders, and the sonar sensor
task display()
{
    while (true)
    {
    	//Displays information about encoders and IR and sonar sensors
			int display = SensorValue[irSensor];
			int sonarValue = SensorValue[sonar];

			nxtDisplayString(0,"%d", display);
			nxtDisplayString(3, "Sonar: %d", sonarValue);
	  }
}
//continues driving until encoders reach destination, then resets motor speed.
void waitForStop()
{
	while(nMotorRunState[backRight] != runStateIdle && nMotorRunState[backLeft] != runStateIdle
		&& nMotorRunState[frontRight] != runStateIdle && nMotorRunState[frontLeft] != runStateIdle)
	{
	}

	motor[backRight] = 0;
	motor[backLeft] = 0;
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
}

void initializeRobot()
{
	ClearTimer(T1);

	int sum = 0;
	for (int i = 0; i < 101; i++) {
		sum += SensorValue[gyro];
		wait1Msec(1);
	}
	initial = sum / 100;
}
