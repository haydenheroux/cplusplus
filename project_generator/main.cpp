#include <filesystem>
#include <fstream>
#include <iostream>

void add_subdirectory(std::string& project_name) {
    std::ofstream cmake_lists{"CMakeLists.txt", std::iostream::app};

    cmake_lists << "add_subdirectory(" << project_name << ")" << std::endl;
}

void write_cmake_lists(std::string& project_name, std::filesystem::path& path) {
    std::ofstream cmake_lists{path};
    
    cmake_lists << "add_executable(" << project_name << " main.cpp)" << std::endl;
}

void write_main_cpp(std::string& project_name, std::filesystem::path& path) {
    std::ofstream main_cpp{path};

    std::string indent = "    ";

    main_cpp << "#include <iostream>\n";
    main_cpp << "\n";
    main_cpp << "int main() {\n";
    main_cpp << indent << "std::cout << \"" << project_name << "\" << std::endl;\n";
    main_cpp << indent << "return 0;\n";
    main_cpp << "}";
}

int main() {
    std::string project_name;

    std::cin >> project_name;

    add_subdirectory(project_name);

    std::filesystem::path project_dir{project_name};

    std::filesystem::create_directory(project_dir);

    std::filesystem::path cmake_lists = project_dir/"CMakeLists.txt";

    if (std::filesystem::exists(cmake_lists) == false) {
        write_cmake_lists(project_name, cmake_lists);
    }

    std::filesystem::path main_cpp = project_dir/"main.cpp";

    if (std::filesystem::exists(main_cpp) == false) {
        write_main_cpp(project_name, main_cpp);
    }
}
