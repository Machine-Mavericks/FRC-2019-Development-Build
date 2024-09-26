/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoRun.h"
#include "commands/DriveStraightDistance.h"
#include "commands/DriveTurnToAngle.h"
#include "commands/TiltUp.h"
#include "commands/CameraSwitchPipeline.h"
#include "commands/DriveGoToTarget.h"
#include "commands/ClawOpen.h"

AutoRun::AutoRun() {
  AddParallel(new CameraSwitchPipeline(0));
  AddParallel(new TiltUp());
  AddSequential(new DriveStraightDistance(96.0, 0.45)); 
  AddParallel(new ClawOpen());
  AddSequential(new DriveTurnToAngle(22.0,3.0, 0.5,0.0 )); 
  AddSequential(new DriveStraightDistance(56.0, 0.45)); 
  AddSequential(new DriveGoToTarget(0.35));
  AddSequential(new DriveStraightDistance(-60.0,0.45));
  AddSequential(new DriveTurnToAngle(-90.0,3.0,0.5,0.0));
  AddSequential(new DriveStraightDistance(86,0.45));
  AddSequential(new DriveTurnToAngle(-90.0,3.0,0.5,0.0));
  AddSequential(new DriveStraightDistance(84,0.45));
  AddSequential(new DriveGoToTarget(0.35));
}
