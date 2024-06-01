#include "project.hpp"

int main(int argc, char* argv[]) {
    std::string project_name;
    bool create_files = false;
    bool update_build = false;

    for (int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);

        if (arg[0] == '-' && arg.length() == 2) {
            switch (arg[1]) {
                case 'c':
                    create_files = !create_files;
                    break;
                case 'u':
                    update_build = !update_build;
                    break;
                default:
                    break;
            }
        } else {
            project_name = arg;
        }
    }

    if (project_name.length() == 0) {
        return 1;
    }

    project project{project_name};

    if (create_files) {
        project.create_files();
    }

    if (update_build) {
        project.update_build();
    }

    return 0;
}
