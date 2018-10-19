#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  ,               sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           leftMotor,     tmotorVex393_MC29, PIDControl, encoderPort, I2C_1)
#pragma config(Motor,  port3,           rightMotor,    tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port9,           liftMotor,     tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

static const float ticksPerInch = 0.967 * (627.2 / (4.0 * PI));
// for moving forward or backwords
static const float ticksPerDeg = 1.0 * (ticksPerInch * 12.0 * PI) / 360.0;
// for turning the robotRaise

//static const float timePerDeg =

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void move(float dist, int speed, bool hold)		//used to drive the robot forward
{
	resetMotorEncoder(rightMotor);
	resetMotorEncoder(leftMotor);

	setMotorTarget(rightMotor, dist*ticksPerInch, speed, hold);
	setMotorTarget(leftMotor, dist*ticksPerInch, speed, hold);

	while (!getMotorTargetCompleted(rightMotor) && !getMotorTargetCompleted(leftMotor))
		wait1Msec(10);
}

void spin(float deg, int speed, bool hold)	//used to turn the robot
{
	resetMotorEncoder(rightMotor);
	resetMotorEncoder(leftMotor);

	setMotorTarget(rightMotor, -deg*ticksPerDeg, speed, hold);
	setMotorTarget(leftMotor, deg*ticksPerDeg, speed, hold);

	while (!getMotorTargetCompleted(rightMotor) && !getMotorTargetCompleted(leftMotor))
		wait1Msec(10);
}
void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{

	move(
	72, 70, false);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{

	//PID fixup
	nMotorPIDSpeedCtrl[rightMotor] = RegIdle;
	nMotorPIDSpeedCtrl[leftMotor] = RegIdle;

	// User control code here, inside the loop

	while (true)
	{
		//Driving Motor Control
		motor[leftMotor] = vexRT[Ch3] / 2;
		motor[rightMotor] = vexRT[Ch2] / 2;

		//Lift Motor Control
		if (vexRT[Btn6U] == 1)
		{
			motor[liftMotor] = 60;
		}

		else if (vexRT[Btn6D] == 1)
		{
			motor[liftMotor] = -60;
		}

		else
		{
			motor[liftMotor] = 0;
		}

		sleep(10);
		// This is the main execution loop for the user control program.
		// Each time through the loop your program should update motor + servo
		// values based on feedback from the joysticks.

		// ........................................................................
		// Insert user code here. This is where you use the joystick values to
		// update your motors, etc.
		// ........................................................................

		// Remove this function call once you have "real" code.
		UserControlCodePlaceholderForTesting();
	}
}
