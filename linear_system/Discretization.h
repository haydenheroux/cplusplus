#pragma once

#include "EigenCore.h"
#include <unsupported/Eigen/MatrixFunctions>

// TODO Use units
template <int States, int Inputs>
void DiscretizeAB(const Matrixd<States, States> &contA,
                  const Matrixd<States, Inputs> &contB, double dt,
                  Matrixd<States, States> *discA,
                  Matrixd<States, Inputs> *discB) {
  // M = [A  B]
  //     [0  0]
  Matrixd<States + Inputs, States + Inputs> M;
  M.template block<States, States>(0, 0) = contA;
  M.template block<States, Inputs>(0, States) = contB;
  M.template block<Inputs, States + Inputs>(States, 0).setZero();

  // ϕ = eᴹᵀ = [A_d  B_d]
  //           [ 0    I ]
  Matrixd<States + Inputs, States + Inputs> phi = (M * dt).exp();

  *discA = phi.template block<States, States>(0, 0);
  *discB = phi.template block<States, Inputs>(0, States);
}
