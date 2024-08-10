#pragma once

#include "EigenCore.h"
#include "LinearSystem.h"

template <int States, int Inputs, int Outputs> class LinearSystemSim {
public:
  LinearSystemSim(const LinearSystem<States, Inputs, Outputs> &system)
      : plant_(system) {

    x_ = Vectord<States>::Zero();
    y_ = Vectord<Outputs>::Zero();
    u_ = Vectord<Inputs>::Zero();
  }

  void Update(double dt) {
    x_ = plant_.CalculateX(x_, u_, dt);
    y_ = plant_.CalculateY(x_, u_);
  }

  const Vectord<Outputs> &GetOutput() const { return y_; }

  double GetOutput(int row) const { return y_(row); }

  void SetInput(const Vectord<Inputs> &u) { u_ = u; }

  void SetInput(int row, double value) { u_(row) = value; }

  void SetState(const Vectord<States> &state) { x_ = state; }

private:
  LinearSystem<States, Inputs, Outputs> plant_;
  Vectord<States> x_;
  Vectord<Outputs> y_;
  Vectord<Inputs> u_;
};
