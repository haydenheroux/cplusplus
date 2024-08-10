#include "Flywheel.h"
#include "Motor.h"
#include "MotorFeedforward.h"
#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
  Flywheel flywheel{k775Pro, 1.0, 0.00032};

  FlywheelSim sim{flywheel, 0.02};

  MotorFeedforward ff{0.0060861185, 0.0};

  const double kReferenceVelocity = 1500; // radians per second

  double previous_velocity = sim.GetVelocity();

  while (true) {
    double error = kReferenceVelocity - previous_velocity;

    if (fabs(error) < 1e-3) {
      break;
    }

    double volts = ff.CalculateVoltage(kReferenceVelocity, 0.0);

    volts = std::clamp(volts, -12.0, 12.0);

    sim.SetVoltage(volts);
    sim.Update();

    double velocity = sim.GetVelocity();

    std::cout << velocity << '\n';

    previous_velocity = velocity;
  }
}
