#include <fstream>

#include "project.hpp"

void project::create_files() {
  std::filesystem::path project_dir{name};

  std::filesystem::create_directory(project_dir);

  std::filesystem::path cmake_lists = project_dir / "CMakeLists.txt";

  if (std::filesystem::exists(cmake_lists) == false) {
    write_cmake_lists(cmake_lists);
  }

  std::filesystem::path main_cpp = project_dir / "main.cpp";

  if (std::filesystem::exists(main_cpp) == false) {
    write_main_cpp(main_cpp);
  }
}

void project::update_build() { add_subdirectory(); }

void project::add_subdirectory() {
  std::ofstream cmake_lists{"CMakeLists.txt", std::iostream::app};

  cmake_lists << "add_subdirectory(" << name << ")" << std::endl;
}

void project::write_cmake_lists(std::filesystem::path &path) {
  std::ofstream cmake_lists{path};

  cmake_lists << "add_executable(" << name << " main.cpp)" << std::endl;
}

void project::write_main_cpp(std::filesystem::path &path) {
  std::ofstream main_cpp{path};

  std::string indent = "    ";

  main_cpp << "#include <iostream>\n";
  main_cpp << "\n";
  main_cpp << "int main() {\n";
  main_cpp << indent << "std::cout << \"" << name << "\" << std::endl;\n";
  main_cpp << indent << "return 0;\n";
  main_cpp << "}";
}
