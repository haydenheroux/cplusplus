#pragma once

#include <filesystem>
#include <string>

class project {
    public:
        project(std::string &name) : name(name) {}
        void create_files();
        void update_build();
    private:
        std::string& name;
        void add_subdirectory();
        void write_cmake_lists(std::filesystem::path& path);
        void write_main_cpp(std::filesystem::path& path);
};
