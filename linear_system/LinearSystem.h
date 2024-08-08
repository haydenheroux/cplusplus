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
      : m_A(A), m_B(B), m_C(C), m_D(D) {}

  // TODO Use units
  StateVector CalculateX(const StateVector &x, const InputVector &u,
                         double dt) const {
    Matrixd<States, States> d_A;
    Matrixd<States, States> d_B;

    DiscretizeAB(m_A, m_B, dt, &d_A, &d_B);

    return d_A * x + d_B * u;
  }

  OutputVector CalculateY(const StateVector &x, const InputVector &u) const {
    return m_C * x + m_D * u;
  }

private:
  Matrixd<States, States> m_A;
  Matrixd<States, Inputs> m_B;
  Matrixd<Outputs, States> m_C;
  Matrixd<Outputs, Inputs> m_D;
};
