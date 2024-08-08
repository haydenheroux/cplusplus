#include "Flywheel.h"
#include "Motor.h"
#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
  const Flywheel flywheel{k775Pro, 1.0, 0.00032};

  FlywheelSim sim{flywheel, 0.02};

  const double kReference = 1500; // radians per second
  const double kV = 0.0060861185; // volts per radian per second

  double previous_velocity = sim.GetVelocity();

  while (true) {
    double error = kReference - previous_velocity;

    if (fabs(error) < 1e-3) {
      break;
    }

    double ff = kReference * kV;

    double volts = std::clamp(ff, -12.0, 12.0);

    sim.SetVoltage(volts);
    sim.Update();

    double velocity = sim.GetVelocity();

    std::cout << velocity << '\n';

    previous_velocity = velocity;
  }
}
