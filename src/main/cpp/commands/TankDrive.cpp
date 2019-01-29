/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Tank drive command allows robot to be driven in tank mode.
// This is the default command when robot in teleop mode

#include "commands/TankDrive.h"
#include "Robot.h"
#include <math.h>
#include "RobotMap.h"

TankDrive::TankDrive() {

  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_MainDrive);

  // tank drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);

}

// Called just before this Command runs the first time
void TankDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TankDrive::Execute() {

  // create variables for left and right joystick y axes
  float raw_left_y, raw_right_y, left_y, right_y;

  // get joystick y values from joystick
  raw_left_y = Robot::m_DriverOI.LeftJoystick->GetRawAxis(1);
  raw_right_y = Robot::m_DriverOI.RightJoystick->GetRawAxis(1);

  // implement throttle curve
  right_y = LINEAR_WEIGHT * raw_right_y + CUBIC_WEIGHT * pow(raw_right_y, 3); 
  left_y = LINEAR_WEIGHT * raw_left_y + CUBIC_WEIGHT * pow(raw_left_y, 3); 

  // set main drive tank speeds
  Robot::m_MainDrive.TankDrive (left_y, right_y);

}

// Make this return true when this Command no longer needs to run execute()
bool TankDrive::IsFinished() {
  
  // since this is default mode, always return false - command never ends
  return false;

}

// Called once after isFinished returns true
void TankDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDrive::Interrupted() {}