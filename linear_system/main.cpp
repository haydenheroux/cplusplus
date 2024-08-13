#include "AutoRun.h"
#include "Flywheel.h"
#include "Motor.h"
#include <iostream>

int main() {
  Flywheel flywheel{k775Pro * 4, 1.0, 0.00032};

  std::cout << "flywheel.motor.Kv_: " << 1.0 / flywheel.motor_.Kv_ << '\n';

  AutoRunner runner{0.02, flywheel, 1e-6, 1e-6, 600};

  double velocity_feedforward = runner.AutoRunFeedforward(0.0, 1.0);

  std::cout << "velocity_feedforward: " << velocity_feedforward << '\n';
}
