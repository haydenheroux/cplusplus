#include <iostream>

#include "project.hpp"

int main() {
    std::string project_name;

    std::cin >> project_name;

    project project{project_name};

    project.create_files();
    project.update_build();
}
