/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClawHome.h"
#include "Robot.h"
#include "subsystems/Claw.h"

// Constructor for ClawHome command
ClawHome::ClawHome() {
  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_Claw);

  // tank drive command is interruptable
  SetInterruptible(false);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void ClawHome::Initialize() {
  // initialize homing
  Robot::m_Claw.InitForHoming();
  
  // turn on motor to move claw towards home position
  Robot::m_Claw.SetClawMotorSpeed(-0.3);

  // command is not finished util proven otherwise
  m_Finished = false;
  
  // reset timer
  m_Time = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void ClawHome::Execute() {
  
  // increment timer
  m_Time += 0.02;

   // we are finished when home limit switch is detected closed or time has exceeded 10s
  if (Robot::m_Claw.IsRevLimitSwitchClosed()==true || m_Time > 10.0)
    m_Finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool ClawHome::IsFinished() {   
  return m_Finished;
}

// Called once after isFinished returns true
void ClawHome::End() {

  // stop motor
  Robot::m_Claw.SetClawMotorSpeed(0);

  //reset encoder
  Robot::m_Claw.InitPositionControl();
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void ClawHome::Interrupted() {}
