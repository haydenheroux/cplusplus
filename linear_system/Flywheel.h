#pragma once

#include "LinearSystemSim.h"
#include "Motor.h"

struct Flywheel {
  Flywheel(const Motor &motor, double gearing, double moment_of_inertia)
      : motor(motor), gearing(gearing), moment_of_inertia(moment_of_inertia) {}

  LinearSystem<1, 1, 1> GetLinearSystem() const {
    Matrixd<1, 1> A;
    A << (-1 * gearing * gearing * motor.Kt) /
             (motor.Kv * motor.R * moment_of_inertia);

    Matrixd<1, 1> B;
    B << (gearing * motor.Kt) / (motor.R * moment_of_inertia);

    Matrixd<1, 1> C;
    C << 1;

    Matrixd<1, 1> D;
    D << 0;

    return LinearSystem<1, 1, 1>{A, B, C, D};
  }

  const Motor &motor;
  const double gearing;
  const double moment_of_inertia;
};

class FlywheelSim {
public:
  FlywheelSim(const Flywheel &flywheel, double dt)
      : flywheel(flywheel), dt(dt), sim(flywheel.GetLinearSystem()) {}

  void SetVoltage(double volts) { sim.SetInput(0, volts); }

  void Update() { sim.Update(dt); };

  double GetVelocity() const { return sim.GetOutput(0); };

  double GetMotorVelocity() const { return GetVelocity() * flywheel.gearing; }

public:
  const Flywheel &flywheel;
  const double dt;
  LinearSystemSim<1, 1, 1> sim;
};
