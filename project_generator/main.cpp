#include "options.hpp"
#include "project.hpp"

int main(int argc, char* argv[]) {
    options options{argc, argv};

    if (options.project_name.empty()) {
        return 1;
    }

    project project{options.project_name};

    if (options.create_files) {
        project.create_files();
    }

    if (options.update_build) {
        project.update_build();
    }

    return 0;
}
