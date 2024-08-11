#include "Flywheel.h"
#include "Motor.h"
#include "MotorFeedforward.h"
#include "PDController.h"
#include <algorithm>
#include <iostream>

int direction(double d) { return (0 < d) - (d < 0); }

int main() {
  const double kDt = 0.02;

  Flywheel flywheel{k775Pro, 1.0, 0.00032};

  FlywheelSim sim{flywheel, kDt};

  MotorFeedforward feedforward{0.0060861185, 0.0};

  const double error_tolerance = 1e-3;
  const double error_rate_tolerance = 1e-3;
  PDController feedback{0.267, 0.0, kDt};

  const double kInitialVelocity = sim.GetVelocity();
  const double kReferenceVelocity = 600;

  double previous_velocity = kInitialVelocity;

  while (feedback.ErrorWithin(error_tolerance) == false) {
    double ff_volts = feedforward.CalculateVoltage(kReferenceVelocity, 0.0);
    double fb_volts = feedback.Calculate(sim.GetVelocity(), kReferenceVelocity);

    if (direction(fb_volts) !=
        direction(kReferenceVelocity - kInitialVelocity)) {
      std::cout << "warn: overshot" << '\n';
    }

    std::cout << "ff_volts: " << ff_volts << '\n';
    std::cout << "fb_volts: " << fb_volts << '\n';

    double volts = std::clamp(ff_volts + fb_volts, -12.0, 12.0);

    std::cout << "volts: " << volts << '\n';

    sim.SetVoltage(volts);
    sim.Update();

    double velocity = sim.GetVelocity();

    std::cout << "velocity: " << velocity << '\n';

    previous_velocity = velocity;

    if (feedback.ErrorRateWithin(error_rate_tolerance) &&
        feedback.ErrorWithin(error_tolerance) == false) {
      std::cout << "error: at steady state" << '\n';
      break;
    }
  }
}
