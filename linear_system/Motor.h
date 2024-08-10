#pragma once

struct Motor {
  double Kt_;
  double Kv_;
  double R_;

  Motor(double nominal_voltage, double stall_torque, double stall_current,
        double free_speed_rpm, double free_current) {
    double free_speed_rad_per_sec = (free_speed_rpm / 60.0) * 2 * 3.14159;

    R_ = nominal_voltage / stall_current;
    Kv_ = free_speed_rad_per_sec / (nominal_voltage - R_ * free_current);
    Kt_ = stall_torque / stall_current;
  }
};

const Motor k775Pro{12.0, 0.71, 134, 18730, 0.7};

const Motor kFalcon500{12.0, 4.69, 257, 6380, 1.5};
