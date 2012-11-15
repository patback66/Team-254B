#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           bLeft,         tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port2,           fLeft,         tmotorVex393, openLoop)
#pragma config(Motor,  port3,           atLeft,        tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port4,           abLeft,        tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port5,           rollersLeft,   tmotorVex269, openLoop)
#pragma config(Motor,  port6,           fRight,        tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           rollersRight,  tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port8,           atRight,       tmotorVex269, openLoop)
#pragma config(Motor,  port9,           abRight,       tmotorVex269, openLoop)
#pragma config(Motor,  port10,          bRight,        tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//nMotorEncoder[bLeft];
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//Variable Declarations
//Constants for Autonomous
const float circumference = 12.6;
const int encoderCounts = 360;
const int integratedEncoderCounts = 392;
//Constants for PID
float arm_kP=.5, arm_kI=.5, arm_kD=.5;
float drive_kP=.5, drive_kI=.5, drive_kD=.5;
//PID error variables
float arm_errorSum=0, arm_lastError=0;
float drive_errorSum=0, drive_lastError=0;

//Function declarations

//PID Functions
float UpdateD(float goal, float currentValue) {//driver pid
  float error = goal - currentValue;
  float p = drive_kP * error;
  drive_errorSum += error;
  float i = drive_kI * drive_errorSum;
  float dError = error - drive_lastError;
  float d = drive_kD * dError;
  drive_lastError = error;
  return p + i + d;
}

float UpdateA(float goal, float currentValue) {//arm pid
  float error = goal - currentValue;
  float p = arm_kP * error;
  arm_errorSum += error;
  float i = arm_kI * arm_errorSum;
  float dError = error - arm_lastError;
  float d = arm_kD * dError;
  arm_lastError = error;
  return p + i + d;
}

//Autonomous and General Functions
int distanceToCounts(float distance, int i)
{
    if(i == 0){ //arm encoder is case 0
		  int counts = distance / circumference * encoderCounts;
		  return counts;
	  }
	  else{ //driver encoder is case 1
	    int counts = distance / circumference * integratedEncoderCounts;
		  return counts;
	  }
}
void clearEncoders()
{

}
void motorUnity (int group, int power)
{
		if (abs (power) <= 10) //threshold
		{
			power=0;
		}
		switch(group)
		{
			case 0: //Left Drive
				motor[fLeft] = power;
				motor[bLeft] = power;
				break;
			case 1: //Right Drive
				motor[fRight] = power;
				motor[bRight] = power;
				break;
			case 2: //Arm
				motor[atLeft] = power;
				motor[abLeft] = power;
				motor[atRight] = power;
				motor[abRight] = power;
				break;
			case 3: //Rollers
				motor[rollersLeft] = power;
				motor[rollersRight] = power;
				break;
		}
}
void holdArm()
{
}
void autoFunctions()
{
  //Insert autonomous routine
}
void basicAuto()
{
  motorUnity(3, 127);
  wait10Msec(300);
  motorUnity(3, 0);
}
void basicDriver()
{
    //Basic Driver + Operator controls
    motorUnity (0,vexRT[Ch3]); //Left
		motorUnity (1,vexRT[Ch2]); //Right
	 	motorUnity (2,vexRT[Ch3Xmtr2]); //Arm
	  motorUnity (3,vexRT[Ch2Xmtr2]); //Rollers
}
void pidDrive()
{
  //Insert controls for driver & operator control with PID
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;
  clearEncoders();

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................
  basicAuto();
	//AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
	  basicDriver();

	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................

	 	//UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.

	}
}
