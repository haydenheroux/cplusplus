#pragma once

#include "Discretization.h"
#include "EigenCore.h"

template <int States, int Inputs, int Outputs> class LinearSystem {
public:
  using StateVector = Vectord<States>;
  using InputVector = Vectord<States>;
  using OutputVector = Vectord<States>;

  LinearSystem(const Matrixd<States, States> &A,
               const Matrixd<States, Inputs> &B,
               const Matrixd<Outputs, States> &C,
               const Matrixd<Outputs, Inputs> &D)
      : A_(A), B_(B), C_(C), D_(D) {}

  // TODO Use units
  StateVector CalculateX(const StateVector &x, const InputVector &u,
                         double dt) const {
    Matrixd<States, States> discreteA;
    Matrixd<States, States> discreteB;

    DiscretizeAB(A_, B_, dt, &discreteA, &discreteB);

    return discreteA * x + discreteB * u;
  }

  OutputVector CalculateY(const StateVector &x, const InputVector &u) const {
    return C_ * x + D_ * u;
  }

private:
  Matrixd<States, States> A_;
  Matrixd<States, Inputs> B_;
  Matrixd<Outputs, States> C_;
  Matrixd<Outputs, Inputs> D_;
};
