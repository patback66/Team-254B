#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  armEncoder,     sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           bLeft,         tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port2,           bRight,        tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port3,           aLeft,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           rollersLeft,   tmotorVex269, openLoop)
#pragma config(Motor,  port5,           strafeLeft,    tmotorVex269, openLoop)
#pragma config(Motor,  port6,           strafeRight,   tmotorVex269, openLoop)
#pragma config(Motor,  port7,           rollersRight,  tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port8,           aRight,        tmotorVex393, openLoop)
#pragma config(Motor,  port9,           fRight,        tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port10,          fLeft,         tmotorVex269, openLoop)
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#define TPR 627.2 //Ticks per revolution
float kp = 0.625;
float ki = 0;
float kd = 0.0;
int previousError = 0;
float errorSum = 0;
int motPower = 0;
int attained = 0;
/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////
void motorUnity (int group, int power)
{

    if (abs (power) <= 10) //threshold
		{
			power=0;
		}
		switch(group)
		{
			case 0: //Left Drive
			  //resetDrivePID();
				motor[fLeft] = power;
				motor[bLeft] = power;
				break;
			case 1: //Right Drive
			  //resetDrivePID();
				motor[fRight] = power;
				motor[bRight] = power;
				break;
			case 2: //Arm
				motor[aLeft] = power;
				motor[aRight] = power;
				break;
			case 3: //Rollers
				motor[rollersLeft] = power;
				motor[rollersRight] = power;
				break;
			case 4:
			  motor[strafeLeft] = power;
			  motor[strafeRight] = power;
			  //strafing motor
			  break;

		}
		//robwashere :)
}
void basicDriver()
{

    //Basic Driver + Operator controls
    motorUnity (0,vexRT[Ch3]); //Left
		motorUnity (1,vexRT[Ch2]); //Right

	  motorUnity (3,vexRT[Ch2Xmtr2]); //Rollers
	  if(vexRT[Btn6U])
	  {
	     motorUnity(4, 127);
	  } else if(vexRT[Btn5U])
	  {
	     motorUnity(4, -127);
	  } else
	  {
	    motorUnity(4, 0);
	  }
	  //hold arm
	  if(vexRT[Btn5UXmtr2])
	  {
	    motorUnity(2, 30);
	  }
	  else if (vexRT[Btn6UXmtr2])
	  {
	     motorUnity(2, 20);
	  }
	  else
	  {
      motorUnity (2,vexRT[Ch3Xmtr2]); //Arm
	  }
}
void lift(int power)
{
   motorUnity(2, power);
}
void armPID(int target)
{
  int error = target - SensorValue[armEncoder];
  if (error<20){
  	attained = 1;
  }
  else{
  	attained = 0;
  }
  int derivative = error-previousError;
  motPower = (error*kp+errorSum*ki+derivative*kd);
  lift(-motPower);
  previousError = error;
  errorSum += error/1024.0;
}
void PIDreset(){
  previousError = 0;
  errorSum = 0;
}
void fdrive(int power)
{
  motorUnity(0, power);
  motorUnity(1, power);
}
float leftdistance()
{
	return nMotorEncoder[leftEncoder] / (TPR) * (4*PI);
}
float rightdistance()
{
	return nMotorEncoder[rightEncoder] / (TPR) * (4*PI);
}
void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

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

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
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

	  UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
	}
}
