#pragma once

#include <cmath>
class PDController {
public:
  PDController(double p, double d, double dt) : p_(p), d_(d), dt_(dt) {}

  void SetReference(double reference) { reference_ = reference; }

  double Calculate(double measurement) {
    has_measurement_ = true;

    previous_error_ = error_;

    error_ = reference_ - measurement;

    error_rate_ = (error_ - previous_error_) / dt_;

    return p_ * error_ + d_ * error_rate_;
  }

  double Calculate(double measurement, double reference) {
    SetReference(reference);
    return Calculate(measurement);
  }

  bool ErrorWithin(double tolerance) {
    return has_measurement_ && fabs(error_) < tolerance;
  }

  double ErrorRateWithin(double tolerance) {
    return has_measurement_ && fabs(error_rate_) < tolerance;
  }

private:
  double p_;
  double d_;
  double dt_;

  bool has_measurement_ = false;

  double reference_;
  double error_;
  double previous_error_;
  double error_rate_;
};
