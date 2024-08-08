#pragma once

#include <Eigen/Core>

template <int Size> using Vectord = Eigen::Vector<double, Size>;

template <int Rows, int Cols> using Matrixd = Eigen::Matrix<double, Rows, Cols>;
