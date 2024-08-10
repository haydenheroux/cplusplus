#pragma once

class MotorFeedforward {
public:
  MotorFeedforward(double kV, double kA)
      : volts_per_velocity_(kV), volts_per_acceleration_(kA) {}

  double CalculateVoltage(double velocity, double acceleration) const {
    return volts_per_velocity_ * velocity +
           volts_per_acceleration_ * acceleration;
  }

private:
  double volts_per_velocity_;
  double volts_per_acceleration_;
};
