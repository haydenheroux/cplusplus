#include "Flywheel.h"
#include "Motor.h"
#include "MotorFeedforward.h"
#include "PDController.h"
#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
  const double kDt = 0.02;

  Flywheel flywheel{k775Pro, 1.0, 0.00032};

  FlywheelSim sim{flywheel, kDt};

  MotorFeedforward feedforward{0.0060861185, 0.0};

  const double error_tolerance = 1e-3;
  const double error_rate_tolerance = 1e-3;
  PDController feedback{0.25, 0.0, kDt};

  const double kReferenceVelocity = 1500; // radians per second

  feedback.SetReference(kReferenceVelocity);

  double previous_velocity = sim.GetVelocity();

  while (feedback.ErrorWithin(error_tolerance) == false) {
    double volts = feedforward.CalculateVoltage(kReferenceVelocity, 0.0) +
                   feedback.Calculate(sim.GetVelocity());

    volts = std::clamp(volts, -12.0, 12.0);

    sim.SetVoltage(volts);
    sim.Update();

    double velocity = sim.GetVelocity();

    std::cout << velocity << '\n';

    previous_velocity = velocity;

    if (feedback.ErrorRateWithin(error_rate_tolerance) &&
        feedback.ErrorWithin(error_tolerance) == false) {
      std::cout << "at steady state" << '\n';
    }
  }
}
