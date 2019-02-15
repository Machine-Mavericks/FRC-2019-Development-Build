/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Drive until the encoders read a specified distance in the direction the robot is facing at the outset of the command


#include "commands/DistanceDrive.h"
#include "subsystems/MainDrive.h"
#include "subsystems/NavX.h"
#include "Robot.h"

DistanceDrive::DistanceDrive(float Distance) {

  // Use Requires() here to declare subsystem dependencies
  Requires (&Robot::m_MainDrive);

  // distance drive command is interruptable
  SetInterruptible(true);

  // command is not to run when robot is disabled
  SetRunWhenDisabled(false);
  
  // the robot will drive a certain distance according to the parameter it was passed
  DistanceToDrive = Distance;
}

// Called just before this Command runs the first time
void DistanceDrive::Initialize() {

  //zero the gyro
  Robot::m_NavX.ZeroYaw();

  // reset the encoders
  Robot::m_MainDrive.ResetLeftEncoder();
  Robot::m_MainDrive.ResetRightEncoder();

}

// Called repeatedly when this Command is scheduled to run
void DistanceDrive::Execute() {

  // get the current yaw
  float CurrentYaw = Robot::m_NavX.GetYaw();
  
  // if distance to drive is negative, drive backward, otherwise drive forward at a given speed
  // drive following the gyro at a the initial heading
  if (DistanceToDrive >= 0.0)
    Robot::m_MainDrive.SetArcadeDrive(0.25,-0.04 *CurrentYaw, true);
  else
     Robot::m_MainDrive.SetArcadeDrive(-0.25,-0.04 *CurrentYaw, true);
}

// Make this return true when this Command no longer needs to run execute()
bool DistanceDrive::IsFinished() { 
 
  // Determine the average distance across the left and right encoders
  float AverageDistance = ( Robot::m_MainDrive.GetRightEncoderDistance() + Robot::m_MainDrive.GetLeftEncoderDistance())*0.5;


  // See if we have driven far enough
  if (fabs (AverageDistance) >= fabs(DistanceToDrive))
    return true;
  else
    return false; 
  
  }

// Called once after isFinished returns true
void DistanceDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DistanceDrive::Interrupted() {}