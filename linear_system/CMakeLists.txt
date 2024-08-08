find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_executable(linear_system main.cpp)
target_link_libraries (linear_system Eigen3::Eigen)
