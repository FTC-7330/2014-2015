#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ultrasonic,     sensorSONAR)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     winchMotor,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     hookMotor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     FL,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     BL,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     FR,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     BR,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     collectionMotor, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    leftGate,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    rightGate,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    bucket,               tServoStandard)

#include "JoystickDriver.c"  // Include file to "handle" the Bluetooth messages.

float initial; float heading; float radheading; int lastTime = 0;//initial is the initial Gyro readings. heading is the robot's yaw
float FLset; float FRset; // these stand for front right set and front left set, which refer to wheels on the robot
//FL set is the front-left motor and the back-right motor, and FR set is the other two motors
float joyAngle; // angle of the first joystick



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
#define TOP_HAT_RIGHT 2
#define TOP_HAT_LEFT 6

int joystickLeftX;
int joystickRightX;
int joystickLeftY;
int joystickRightY;
int scaledLeftX;
int scaledRightX;
int scaledLeftY;
int scaledRightY;
int waitTime = 50;
int winchTopPosition = 15415;

int winchPosition = 0;
int winchEncoderPosition = 0;

bool yJoyONEIsPressed;
bool yJoyONEWasPressed;
bool aJoyONEIsPressed;
bool aJoyONEWasPressed;

bool isSuper = true;
bool isCollectorRunning = false;
bool gatesOpen = false;
bool hookDown = true;
bool winchMoving = false;
bool bucketDown = false;


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


void moveDirection(float angle, float magnitude){ // sets the motor sets to move at certain speeds depending on the vector given
	FLset = magnitude * (cos(angle) + sin(angle));
	FRset = magnitude * (sin(angle) - cos(angle));
}

void initializeRobot(){
	nMotorEncoder[winchMotor] = 0; // from our initial program
	// Finds average base gyro reading
	for(int i = 0; i < 100; i++){ //sums up first hundred gyro readings
		initial += SensorValue[S4];
		wait1Msec(10);
	}
	initial = initial / 100; //divides by 100 to find the average reading
  return;
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
	bool lbJoyONEWasPressed = false;
	bool lbJoyONEIsPressed = false;
	bool rbJoyONEIsPressed = false;
	bool rbJoyONEWasPressed = false;

	bool startJoyTWOIsPressed = false;
	bool startJoyTWOWasPressed = false;
	bool lbJoyTWOWasPressed = false;
	bool lbJoyTWOIsPressed = false;
	bool rbJoyTWOIsPressed = false;
	bool rbJoyTWOWasPressed = false;

	yJoyONEIsPressed = false;
	yJoyONEWasPressed = false;
	aJoyONEIsPressed = false;
	aJoyONEWasPressed = false;

	while(true)
	{
			getJoystickSettings(joystick);

			//Joystick 1 Booleans
			startJoyONEIsPressed = (joy1Btn(START_BUTTON)==1);
			rbJoyONEIsPressed = (joy1Btn(RIGHT_BUTTON)==1);
			lbJoyONEIsPressed = (joy1Btn(LEFT_BUTTON)==1);

			//Joystick 2 Booleans
			rbJoyTWOIsPressed = (joy2Btn(RIGHT_BUTTON)==1);
			startJoyTWOIsPressed = (joy2Btn(START_BUTTON)==1);
			isTurbo = (joy2Btn(LEFT_BUTTON)==1);
			yJoyONEIsPressed = (joy1Btn(BUTTON_Y)==1);
			aJoyONEIsPressed = (joy1Btn(BUTTON_B)==1);

			//Toggle to tank drive (which doesn't work).
			if(startJoyONEIsPressed&&!startJoyONEWasPressed)
			{
				isSuper = !isSuper;
			}
			//Toggle collector.
			if(yJoyONEIsPressed&&!yJoyONEWasPressed)
			{
				isCollectorRunning = !isCollectorRunning;
			}
			//Toggle goal grabbing hook
			if(rbJoyONEIsPressed&&!rbJoyONEWasPressed)
			{
				hookDown = !hookDown;
			}
			//Toggle open gates
			if(lbJoyONEIsPressed&&!lbJoyONEWasPressed)
			{
				gatesOpen = !gatesOpen;
			}
			//Toggles the bucket
			if(aJoyONEIsPressed && !aJoyONEWasPressed)
			{
				bucketDown = !bucketDown;
			}
      if(joy1Btn(BUTTON_X) == 1)
      {
      	nMotorEncoder[winchMotor] = 0;
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
			rbJoyONEWasPressed = rbJoyONEIsPressed;
			lbJoyONEWasPressed = lbJoyONEIsPressed;

			startJoyTWOWasPressed = startJoyTWOIsPressed;
			rbJoyTWOWasPressed = rbJoyTWOIsPressed;
			lbJoyTWOWasPressed = lbJoyTWOIsPressed;
			yJoyONEWasPressed = yJoyONEIsPressed;
			aJoyONEWasPressed = aJoyONEIsPressed;
			// wait1Msec(waitTime);
	}
}

task Collection()
{

	while(true)
	{
		if(isCollectorRunning)
		{
			motor[collectionMotor] = -80;
		}
		else
		{
			motor[collectionMotor] = 0;
		}

		wait1Msec(waitTime);
	}
}

task printServo()
{
	while (true)
	{
		nxtDisplayString(1, "right gate: %d", servo[rightGate]);
		nxtDisplayString(2, "left gate: %d", servo[leftGate]);
		nxtDisplayString(3, "w encoder: %d", nMotorEncoder[winchMotor]);
		wait1Msec(10);
	}
}
task Winch()  //Written by Jake (winch)
{
	//initial bucket values
	int bucketUpPos = 150;
	int bucketDownPos = 50;

	while(true)//manual winch movement
	{
		//When the top of the D-pad is pushed up, it will raise up at a power of 60.
		if (joystick.joy1_TopHat == TOP_HAT_UP && nMotorEncoder[winchMotor] < 15415)
		{
			winchMoving = true;
			motor[winchMotor] = 60;
		}
		//When the bottom of the D-pad is pushed down, it will lower at a power of 60.
		else if (joystick.joy1_TopHat == TOP_HAT_DOWN)
		{
			winchMoving = true;
			motor[winchMotor] = -60;
		}
		else if(joystick.joy1_TopHat == TOP_HAT_RIGHT)
		{
			while(nMotorEncoder[winchMotor] < 15415)
			{
				winchMoving = true;
			  motor[winchMotor] = 60;
		  }
	  }
	  else if(joystick.joy1_TopHat == TOP_HAT_LEFT)
		{
			while(nMotorEncoder[winchMotor] > 50)
			{
				winchMoving = true;
			  motor[winchMotor] = -60;
		  }
	  }
		//When neither up nor down is pushed, the bucket stays still.
		else
		{
			winchMoving = false;
			motor[winchMotor] = 0;
		}
		//Opens bucket (and stays open).
		if(bucketDown)
		{
			if(servo[bucket] > 60)
		  	servo[bucket] = 60;
		  else if(servo[bucket] <= 60)
		  {
		     wait1Msec(500);
		     servo[bucket] = 50;
		  }

		}
		//Closes bucket (and stays closed).
		else if(!bucketDown)
		{

		  servo[bucket] = bucketUpPos;
		}
	}
}


task GoalGrabber()
{
	int leftGateClosedPos = 165;
	int leftGateOpenPos = 45;
	int rightGateClosedPos = 45;
	int rightGateOpenPos = 165;
	int hookUpPos = 40;
	int hookDownPos = 20;

	while (true)
	{
		if(gatesOpen && servoTarget[leftGate] != leftGateOpenPos && servoTarget[rightGate] != rightGateOpenPos )
		{
			servo[leftGate] = leftGateOpenPos;
			servo[rightGate]= rightGateOpenPos;
		}
		else if(!gatesOpen && servoTarget[leftGate] != leftGateClosedPos && servoTarget[rightGate] != rightGateClosedPos )
		{
			servo[leftGate] = leftGateClosedPos;
			servo[rightGate]= rightGateClosedPos;
		}

		if(hookDown && nMotorEncoder[hookMotor]> hookDownPos)
		{
			motor[hookMotor] = -5;
		}
		else if(!hookDown && nMotorEncoder[hookMotor] < hookUpPos)
		{
			motor[hookMotor] = 5;
		}
		else
		{
			motor[hookMotor] = 0;
		}
	}
}

// This is the superdrive task. If you can think of any better names, please tell me :P
// This task incorporates two modes, regular mecanum driving and free-spinning mode
task superDrive(){
while(true)
{
if(isSuper)
{

	float x1,y1,x2,y2,LF,RF,LB,RB = 0;
	int minJoy = 12;
	float turning;
	float mag; // magnitude of the joystick vector
	float initialHeading = radheading;
	float calcHeading = radheading; // sets a base heading for the
	float movementAmount, turningAmount, totalAmount; // for apportioning power to turning and moving
	while(isSuper) { // while true
		// Get joystick values
		x1 = joystick.joy1_x1 * .5;
		y1 = joystick.joy1_y1 * .5;
		x2 = joystick.joy1_x2 * .5;
		y2 = joystick.joy1_y2 * .5;
		// function for making new initial heading


		if (joy1Btn(5) == 1){
			initialHeading = radheading;
		}
		// starts free-spinning mode
		if (isSuper) {
			// find joystick vector angle
			joyAngle = atan2(y1, x1);
			// find joystick vector magnitude
			mag = sqrt(x1*x1+y1*y1)/2;
			if (mag>64)
				mag = 64;
			// get calculated heading
			calcHeading = radheading - initialHeading;
			// find the direction needed to move
	    	moveDirection(joyAngle + calcHeading, mag);
	    	// fix movement drifting
	    	if (abs(joystick.joy1_x1)<minJoy&&abs(joystick.joy1_y1)<minJoy&&abs(joystick.joy1_x2)<minJoy){
				FLset=0;FRset=0;
			}
			// find turning magnitude
			turning = x2 / 2;
			//fix turning drifting
			if (abs(joystick.joy1_x2) < minJoy) {
				turning = 0;
			}
			// apportion motor capacity to movement and turning
			// TODO make this better... although that will be difficult
			totalAmount = 1 + turning + mag*3;
			movementAmount = (mag*3)/totalAmount;
			turningAmount = turning/totalAmount;
			// Apply finished values to motors
	  	motor[FL] = 2*FLset*movementAmount+2*turning*turningAmount;
			motor[FR] = 2*FRset*movementAmount-2*turning*turningAmount;
			motor[BL] = 2*FRset*movementAmount+2*turning*turningAmount;
			motor[BR] = 2*FLset*movementAmount-2*turning*turningAmount;
		 	nxtDisplayCenteredTextLine(4, "else block");
			} else {

			// Resets movement values
			LF = 0;
			RF = 0;
			LB = 0;
			RB = 0;
			// Get joystick values
			x1 = joystick.joy1_x1 * .5;
			y1 = joystick.joy1_y1 * .5;
			x2 = joystick.joy1_x2 * .5;
			y2 = joystick.joy1_y2 * .5;
			// Handle Strafing Movement
			LF += x1;
			RF -= x1;
			LB -= x1;
			RB += x1;
			// Handle Regular Movement
			LF += y1;
			RF += y1;
			LB += y1;
			RB += y1;
			// Handle Turning Movement
			LF += x2;
			RF -= x2;
			LB += x2;
			RB -= x2;
			if (abs(joystick.joy1_x1)<minJoy&&abs(joystick.joy1_y1)<minJoy&&abs(joystick.joy1_x2)<minJoy){
				LF = 0;
				RF = 0;
				LB = 0;
				RB = 0;
			}
			// Apply Finished values to motors.
			nxtDisplayCenteredTextLine(4, "else block");
			motor[FL] = LF; // initially no shift
			motor[FR] = RF;
			motor[BL] = LB;
			motor[BR] = RB;
		}
		wait1Msec(10);
	}
}
else
{

	// mecanum driving
	// 242 could be more precise
	// think about implementing dampening and quadratic shifting
	while(!isSuper)
	{

			motor[FL] = (scaledLeftY - scaledRightX + scaledLeftX);
			motor[BL] =  (scaledLeftY - scaledRightX - scaledLeftX);
			motor[FR] = (scaledLeftY + scaledRightX - scaledLeftX);
			motor[BR] = (scaledLeftY + scaledRightX + scaledLeftX);

			// motor[frontLeft] = (joystickLeftY - joystickRightX + joystickLeftX)*100/127;
			// motor[backLeft] =  (joystickLeftY - joystickRightX - joystickLeftX)*100/127;
			// motor[frontRight] = (joystickLeftY + joystickRightX - joystickLeftX)*100/127;
			// motor[backRight] = (joystickLeftY + joystickRightX + joystickLeftX) *100/127;

		wait1Msec(waitTime);
	}
}
}
}

// This task finds the heading of the robot using the gyro.
// Keep in mind that this needs the code written in the initializeRobot() function to work
task findHeading(){
	ClearTimer(T1); // sets timer to 0
	while(true){
		int currentReading = SensorValue[gyro] - initial; // gets the new sensor reading
		heading += (currentReading) * (time1[T1] - lastTime) * .001; // modifies the header
		lastTime = time1[T1]; // sets the last time for the next reading
		if (time1[T1]>30000){ // this resets the timer after 30 seconds
			ClearTimer(T1);
			lastTime = 0;
		}
		radheading = heading/180*PI; // the heading expressed in radians
		wait1Msec(10); // lets other tasks run
	}

}



// This is a task mostly for debugging. It displays values for the heading and joystick angle
// This task is not essential and can be deleted
task display(){
	while (true){
		eraseDisplay();
		//nxtDisplayCenteredTextLine(0, "Color: %d", c);
		nxtDisplayCenteredTextLine(0, "Heading: %d", heading);
		nxtDisplayCenteredTextLine(1, "joyAngle: %d", joyAngle);
		nxtDisplayCenteredTextLine(2, "gyro: %d", SensorValue[gyro]);
		wait1Msec(20);
	}
}

task main(){
  initializeRobot();
  nMotorEncoder[hookMotor] = 0;
  //waitForStart();   // wait for start of tele-op phase
  startTask(display);
  startTask(findHeading);
  startTask(superDrive);
	startTask(Collection);
	startTask(Winch);
	startTask(PrintServo);
	startTask(GoalGrabber);
	// startTask(Display);
	inputManager();
  while (true)
  {
	  wait1Msec(10000);
  }
}
