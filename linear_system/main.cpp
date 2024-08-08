#include "EigenCore.h"
#include "LinearSystem.h"
#include "LinearSystemSim.h"
#include <cmath>
#include <iostream>

double calculate_Kt(double stall_torque, double stall_current) {
  return stall_torque / stall_current;
}

double calculate_R(double voltage, double stall_current) {
  return voltage / stall_current;
}

double calculate_Kv(double free_speed, double voltage, double free_current,
                    double resistance) {
  return free_speed / (voltage - free_current * resistance);
}

Matrixd<1, 1> flywheel_A(double G, double Kt, double Kv, double R, double J) {
  Matrixd<1, 1> A;

  A << (-1 * G * G * Kt) / (Kv * R * J);

  return A;
}

Matrixd<1, 1> flywheel_B(double G, double Kt, double R, double J) {
  Matrixd<1, 1> B;

  B << (G * Kt) / (R * J);

  return B;
}

Matrixd<1, 1> flywheel_C() {
  Matrixd<1, 1> C;

  C << 1;

  return C;
}

Matrixd<1, 1> flywheel_D() {
  Matrixd<1, 1> D;

  D << 0;

  return D;
}

int main() {
  const double dt = 0.02;

  const double stall_torque = 4.69;
  const double stall_current = 257;
  const double voltage = 12.0;
  const double free_speed = (6380.0 / 60.0) * 3.14159 * 2.0;
  const double free_current = 1.5;

  const double G = 12.0 / 18.0;
  const double Kt = calculate_Kt(stall_torque, stall_current);
  const double R = calculate_R(voltage, stall_current);
  const double Kv = calculate_Kv(free_speed, voltage, free_current, R);
  const double J = 0.00032;

  const Matrixd<1, 1> A = flywheel_A(G, Kt, Kv, R, J);
  const Matrixd<1, 1> B = flywheel_B(G, Kt, R, J);
  const Matrixd<1, 1> C = flywheel_C();
  const Matrixd<1, 1> D = flywheel_D();

  const LinearSystem<1, 1, 1> sys{A, B, C, D};

  LinearSystemSim<1, 1, 1> sim{sys};

  double u = 12.0;

  double y = sim.GetOutput(0);

  double eps = 1e-6;

  while (true) {
    sim.SetInput(0, u);
    sim.Update(dt);
    std::cout << sim.GetOutput(0) << '\n';

    if (fabs(sim.GetOutput(0) - y) < eps) {
      break;
    }

    y = sim.GetOutput(0);
  }
}
