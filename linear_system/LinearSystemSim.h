#pragma once

#include "EigenCore.h"
#include "LinearSystem.h"
template <int States, int Inputs, int Outputs> class LinearSystemSim {
public:
  LinearSystemSim(const LinearSystem<States, Inputs, Outputs> &system)
      : m_plant(system) {

    m_x = Vectord<States>::Zero();
    m_y = Vectord<Outputs>::Zero();
    m_u = Vectord<Inputs>::Zero();
  }

  // TODO Use units
  void Update(double dt) {
    m_x = m_plant.CalculateX(m_x, m_u, dt);
    m_y = m_plant.CalculateY(m_x, m_u);
  }

  const Vectord<Outputs> &GetOutput() const { return m_y; }

  double GetOutput(int row) const { return m_y(row); }

  void SetInput(const Vectord<Inputs> &u) { m_u = u; }

  void SetInput(int row, double value) { m_u(row) = value; }

  void SetState(const Vectord<States> &state) { m_x = state; }

private:
  LinearSystem<States, Inputs, Outputs> m_plant;
  Vectord<States> m_x;
  Vectord<Outputs> m_y;
  Vectord<Inputs> m_u;
};
