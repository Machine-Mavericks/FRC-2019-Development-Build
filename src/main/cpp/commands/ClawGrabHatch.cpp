/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClawGrabHatch.h"
#include "Robot.h"
#include "RobotMap.h"

// default position is open
static int position = CLAW_HATCH_POSITION;

ClawGrabHatch::ClawGrabHatch() {
  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_Claw);

  // tank drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
}

// Called just before this Command runs the first time
void ClawGrabHatch::Initialize() {

  // set Claw target position
  Robot::m_Claw.SetClawTargetPosition(2);
  
}

// Called repeatedly when this Command is scheduled to run
void ClawGrabHatch::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ClawGrabHatch::IsFinished() {
  return Robot::m_Claw.IsClawAtTarget(); }

// Called once after isFinished returns true
void ClawGrabHatch::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClawGrabHatch::Interrupted() {}
