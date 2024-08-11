#pragma once

#include "Flywheel.h"
#include "MotorFeedforward.h"
#include "PDController.h"

inline int Direction(double d) { return (0 < d) - (d < 0); }

class AutoRunner {
public:
  AutoRunner(double dt, const Flywheel &flywheel, double tolerance,
             double rate_tolerance, double reference_velocity)
      : dt_(dt), flywheel_(flywheel), tolerance_(tolerance),
        rate_tolerance_(rate_tolerance),
        reference_velocity_(reference_velocity) {}

  double AutoRunFeedforward(double minimum, double maximum) {
    double guess;

    while (true) {
      guess = minimum + 0.5 * (maximum - minimum);

      MotorFeedforward feedforward{guess, 0.0};
      PDController feedback{0.0, 0.0, dt_};

      double error = AutoRun(feedforward, feedback);

      if (fabs(error) < tolerance_) {
        break;
      }

      bool overshot = Direction(error) != Direction(reference_velocity_);

      if (overshot) {
        maximum = guess;
      } else {
        minimum = guess;
      }
    }

    return guess;
  }

  double AutoRun(MotorFeedforward feedforward, PDController feedback) {
    FlywheelSim sim{flywheel_, dt_};

    double previous_error = 0.0;
    double error = reference_velocity_ - sim.GetVelocity();

    double error_rate = (error - previous_error) / dt_;

    while (fabs(error_rate) > rate_tolerance_) {
      double feedforward_voltage =
          feedforward.CalculateVoltage(reference_velocity_, 0.0);

      double feedback_voltage =
          feedback.Calculate(sim.GetVelocity(), reference_velocity_);

      sim.SetVoltage(feedforward_voltage + feedback_voltage);
      sim.Update();

      previous_error = error;
      error = reference_velocity_ - sim.GetVelocity();

      bool overshot = Direction(error) != Direction(reference_velocity_);

      if (overshot) {
        return error;
      }

      error_rate = (error - previous_error) / dt_;

      if (error_rate > 0) {
        return error;
      }
    }

    return error;
  }

private:
  double dt_;

  Flywheel flywheel_;

  double tolerance_;
  double rate_tolerance_;

  double reference_velocity_;
};
