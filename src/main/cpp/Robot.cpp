/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

RobotPrefs Robot::m_Prefs;
DriverOI Robot::m_DriverOI;
MechanismOI Robot::m_MechanismOI;
DashboardOI Robot::m_DashboardOI;
MainDrive Robot::m_MainDrive;
NavX Robot::m_NavX;
Elevator Robot::m_Elevator;
Limelight Robot::m_Limelight;
CameraTilt Robot::m_CameraTilt;
IntakeTilt Robot::m_IntakeTilt;
TiltHome Robot::m_TiltHome;
ClawHome Robot::m_ClawHome;
Claw Robot::m_Claw;
Snowblower Robot::m_Snowblower;
LobClaw Robot::m_LobClaw;
IndicatorLight Robot::m_IndicatorLight;
ChangeLight Robot::m_ChangeLight;

// ------------------------ General (All Modes) --------------------

// Function is called when the robot object is first created
void Robot::RobotInit() {
  //m_chooser.SetDefaultOption("Default TeleOp", &m_defaultTeleOp);
  //m_chooser.AddOption("My Auto", &m_myAuto);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);


  m_Prefs.ResetToDefaults();

  m_ChangeLight.Start();


}

// This function is called every robot packet, no matter the mode. Use
// this for items like diagnostics that you want ran during disabled,
// autonomous, teleoperated and test.
// <p> This runs after the mode specific periodic functions, but before
// LiveWindow and SmartDashboard integrated updating. */
void Robot::RobotPeriodic() {
  
  // update driver dashboard
  m_DashboardOI.UpdateDashBoard();
}


// ------------------------ Disabled Mode --------------------

// This function is called once each time the robot enters Disabled mode. You
// can use it to reset any subsystem information you want to clear when the
// robot is disabled.
void Robot::DisabledInit() {
}

// This function is called every time period while robot is in Disabled Mode
void Robot::DisabledPeriodic() {
    // run scheduler to operator any commands as required
  frc::Scheduler::GetInstance()->Run();
  }


// ------------------------ Autonomous Mode --------------------

// This autonomous (along with the chooser code above) shows how to select
// between different autonomous modes using the dashboard. The sendable chooser
// code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
// remove all of the chooser code and uncomment the GetString code to get the
// auto name from the text box below the Gyro.
// You can add additional auto modes by adding additional commands to the
// chooser code above (like the commented example) or additional comparisons to
// the if-else structure below with additional strings & commands. */
void Robot::AutonomousInit() {
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }
  m_autonomousCommand = m_chooser.GetSelected();
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Start();
  }
}

// This function is called every tiem period while robot is in Autonomous Mode
void Robot::AutonomousPeriodic() {
    // run scheduler to operator any commands as required
  frc::Scheduler::GetInstance()->Run();
  }


// ------------------------ Teleop Mode --------------------

// This function is called once each time the robot enters Teleop mode. 
void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. 
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }

  // temporary //
  // reset elevator to home position (CAUTION: assumes elevator is down)
  m_Elevator.ResetEncoderPosition();
  m_Elevator.SetElevatorTargetAnalog(0);
  
  #ifdef ROBOTTYPE_CLAW
    m_TiltHome.Start();
    m_ClawHome.Start();
  #endif

  #ifdef ROBOTTYPE_SNOWBLOWER
    m_IntakeTilt.InitPositionControl();
  #endif
}

// This function is called every time period while robot is in TeleOp Mode
void Robot::TeleopPeriodic() {
  // run scheduler to operator any commands as required
  frc::Scheduler::GetInstance()->Run();
  }


// ------------------------ Test Mode --------------------

// This function is called every tiem period while robot is in Test Mode
void Robot::TestPeriodic() {
  }


// ------------------------ Main Program --------------------


// create a robot object
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
