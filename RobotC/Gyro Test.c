#pragma config(Sensor, S1,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,          rightMotor,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//tyler is better than rohan

float degHeading;
float initial;
float radHeading;
int lastTime = 0;

task heading()
{
	ClearTimer(T1); // sets timer to 0

	while(true)
	{
		int currentVelocity = SensorValue[gyro] - initial; // gets the new sensor reading
		degHeading += (currentVelocity) * (time1[T1] - lastTime) * .001; // modifies the header
		lastTime = time1[T1]; // sets the last time for the next reading
		if (time1[T1] > 30000) // this resets the timer after 30 seconds
		{
			ClearTimer(T1);
			lastTime = 0;
		}
		radheading = degHeading / 180 * PI; // the heading expressed in radians
		wait1Msec(10); // lets other tasks run
	}
}

float min(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}

float getPower(float degreesRemaining)
{
	return 15 * (min(15, degreesRemaining) / 15);
}

void turn()
{
		float degreesToTurn = 89;
		float degreesSoFar = 0;
		float initialTurnReading = SensorValue[gyro];

		//nSyncedMotors = synchAB;
		//nSyncedTurnRatio = -100;

		float degreesRemaining = (degreesToTurn - degreesSoFar);
		while(abs(degreesToTurn) >= abs(degreesSoFar))
		{
			nxtDisplayString(1, "Degrees: %d                      ", degreesRemaining);
			int power = (int) getPower(degreesRemaining);
			motor[motorA] = power;
			motor[motorB] = -power;
			wait1Msec(10);
			float currentGyroReading = SensorValue[gyro] - initialTurnReading;
			degreesSoFar = degreesSoFar + currentGyroReading*.01;
			degreesRemaining = (degreesToTurn - degreesSoFar);
		}
		motor[motorA] = 0;
		motor[motorB] = 0;
		wait1Msec(500);
}

task main()
{
		for(int i = 0; i < 4; i++)
		{
			turn();
		}

}
