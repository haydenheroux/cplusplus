#include <vector>

#include "options.hpp"

options::options(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);

    for (auto& arg : args) {
        if (arg[0] == '-') {
            std::string options = arg.substr(1, arg.length() - 1);

            for (auto option : options) {
                parse_option(option);
            }
        } else {
            project_name = arg;
        }
    }
}

void options::parse_option(char option) {
    switch (option) {
        case 'c':
            create_files = !create_files;
            break;
        case 'u':
            update_build = !update_build;
            break;
        default:
            break;
    }
}
