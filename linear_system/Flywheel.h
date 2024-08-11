#pragma once

#include "LinearSystemSim.h"
#include "Motor.h"

struct Flywheel {
  Flywheel(const Motor &motor, double gearing, double moment_of_inertia)
      : motor_(motor), gearing_(gearing),
        moment_of_intertia_(moment_of_inertia) {}

  LinearSystem<1, 1, 1> GetLinearSystem() const {
    Matrixd<1, 1> A;
    A << (-1 * gearing_ * gearing_ * motor_.Kt_) /
             (motor_.Kv_ * motor_.R_ * moment_of_intertia_);

    Matrixd<1, 1> B;
    B << (gearing_ * motor_.Kt_) / (motor_.R_ * moment_of_intertia_);

    Matrixd<1, 1> C;
    C << 1;

    Matrixd<1, 1> D;
    D << 0;

    return LinearSystem<1, 1, 1>{A, B, C, D};
  }

  Motor motor_;
  double gearing_;
  double moment_of_intertia_;
};

class FlywheelSim {
public:
  FlywheelSim(const Flywheel &flywheel, double dt)
      : flywheel_(flywheel), dt_(dt), sim_(flywheel.GetLinearSystem()) {}

  void SetVoltage(double volts) {
    volts = std::clamp(volts, -12.0, 12.0);
    sim_.SetInput(0, volts);
  }

  void Update() { sim_.Update(dt_); };

  double GetVelocity() const { return sim_.GetOutput(0); };

  double GetMotorVelocity() const { return GetVelocity() * flywheel_.gearing_; }

public:
  Flywheel flywheel_;
  double dt_;
  LinearSystemSim<1, 1, 1> sim_;
};
