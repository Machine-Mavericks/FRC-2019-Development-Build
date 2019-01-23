/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>


class TestSolenoid : public frc::Subsystem {
 private:
  frc::DoubleSolenoid m_doubleSolenoid{1, 2};

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  TestSolenoid();
  void InitDefaultCommand() override;
  void SetSolenoid(void);

};