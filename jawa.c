#pragma config(Motor,  port1,           crushLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           leftD1,        tmotorVex269, openLoop)
#pragma config(Motor,  port3,           leftD2,        tmotorVex269, openLoop)
#pragma config(Motor,  port4,           arm,           tmotorVex393, openLoop)
#pragma config(Motor,  port7,           claw,          tmotorVex269, openLoop)
#pragma config(Motor,  port8,           rightD1,       tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port9,           rightD2,       tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port10,          crushRight,    tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

void motorUnity(int group, int power)
{
  if(abs(power) <= 10)
    power = 0;
  switch(group)
  {
    case 0: //left
      motor[leftD1] = power;
      motor[leftD2] = power;
      break;
    case 1: //right
      motor[rightD1] = power;
      motor[rightD2] = power;
      break;
    case 2: //crusher
      motor[crushLeft] = power;
      motor[crushRight] = power;
      break;
    case 3: //arm
      motor[arm] = power;
      break;
    case 4:
      motor[claw] = power;
      break;
  }
}
void drive()
{
  motorUnity(0, vexRT[Ch3]);
  motorUnity(1, vexRT[Ch2]);
  if(vexRT[Btn5U] == 1)
  {
    motorUnity(2, 127);
  }
  else if(vexRT[Btn5D] == 1)
  {
    motorUnity(2, -127);
  }
  else
  {
    motorUnity(2, 0);
  }
  if(vexRT[Btn6U] == 1)
  {
    motorUnity(3, 75);
  }
  else if(vexRT[Btn6D] == 1)
  {
    motorUnity(3, -75);
  }
  else
  {
    motorUnity(3, 0);
  }
  if(vexRT[Btn8U] == 1)
  {
    motorUnity(4, 127);
  }
  else if(vexRT[Btn8D] == 1)
  {
    motorUnity(4, -127);
  }
  else
  {
    motorUnity(4, 0);
  }
}
void pre_auton()
{
  bStopTasksBetweenModes = true;
}
task autonomous()
{
	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}
task usercontrol()
{
	while (true)
	{
    drive();
	}
}
